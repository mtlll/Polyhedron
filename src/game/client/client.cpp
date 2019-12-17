#include "engine/engine.h"

#include "shared/networking/network.h"
#include "shared/networking/cl_sv.h"
#include "shared/networking/protocol.h"
#include "shared/networking/frametimestate.h"

#include "shared/entities/coreentity.h"
#include "shared/entities/baseentity.h"
#include "shared/entities/basedynamicentity.h"
#include "shared/entities/basecliententity.h"

#include "game/game.h"
#include "game/client/client.h"
#include "game/server/server.h"
#include "game/entities/player.h"

namespace game {
    namespace client {
        // Radar scales.
        VARP(minradarscale, 0, 384, 10000);
        VARP(maxradarscale, 1, 1024, 10000);
        VARP(radarteammates, 0, 1, 1);
        FVARP(minimapalpha, 0, 1, 1);

        void GameConnect(bool _remote)
        {
            game::remote = _remote;
            conoutf("Connected");
            // Toggle edit mode if required.
            if(editmode)
                toggleedit();
        }

        SCRIPTEXPORT_AS(changemap) void ChangeMap(const char *name)
        {
            // Are we connected? If not, connect locally.
            if(!connected) LocalConnect();

            // Toggle edit mode if required.
            if(editmode)
                toggleedit();

            // If world loading fails, start a new empty map instead.
            if(!load_world(name))
                emptymap(0, true, name);
        }

        void ForceEdit(const char *name) {
            // Trigger a changemap by force edit, which in return toggles edit mode.
            ChangeMap(name);
        }
                
        // collect c2s messages conveniently
        vector<uchar> messages;
        int messageClientNumber = -1, messageReliable = false;

        bool AddMessage(game::networking::protocol::NetClientMessage type, const char *fmt, ...) {
            if(!connected) return false;
            static uchar buf[MAXTRANS];
            ucharbuf p(buf, sizeof(buf));
            game::networking::putint(p, static_cast<int>(type));
            int numi = 1, numf = 0, nums = 0, mcn = -1;
            bool reliable = false;
            if(fmt)
            {
                va_list args;
                va_start(args, fmt);
                while(*fmt) switch(*fmt++)
                {
                    case 'r': reliable = true; break;
                    case 'c':
                    {
                        auto d = dynamic_cast<entities::classes::BaseClientEntity*>( va_arg(args, entities::classes::CoreEntity*) );
                        mcn = (d ? (!d || d == game::player1 ? -1 : d->ci.clientNumber) : -1);
                        break;
                    }
                    case 'v':
                    {
                        int n = va_arg(args, int);
                        int *v = va_arg(args, int *);
                        loopi(n) game::networking::putint(p, v[i]);
                        numi += n;
                        break;
                    }

                    case 'i':
                    {
                        int n = isdigit(*fmt) ? *fmt++-'0' : 1;
                        loopi(n) game::networking::putint(p, va_arg(args, int));
                        numi += n;
                        break;
                    }
                    case 'f':
                    {
                        int n = isdigit(*fmt) ? *fmt++-'0' : 1;
                        loopi(n) game::networking::putfloat(p, (float)va_arg(args, double));
                        numf += n;
                        break;
                    }
                    case 's': game::networking::sendcubestr(va_arg(args, const char *), p); nums++; break;
                    case 'S': game::networking::sendcubestr(va_arg(args, const char *), p); nums++; break; // TODO: Allow it to fetch std::string

                }
                va_end(args);
            }
            int num = nums || numf ? 0 : numi, msgsize = ::server::MessageSizeLookup(type);
            if(msgsize && num!=msgsize) { fatal("inconsistent msg size for %d (%d != %d)", type, num, msgsize); }
            if(reliable) messageReliable = true;
            if(mcn != messageClientNumber)
            {
                static uchar mbuf[16];
                ucharbuf m(mbuf, sizeof(mbuf));
                networking::putint(m, static_cast<int>(networking::protocol::Events::FromAI));
                networking::putint(m, mcn);
                messages.put(mbuf, m.length());
                messageClientNumber = mcn;
            }
            messages.put(buf, p.length());
            return true;
        }

        void ConnectAttempt(const char *name, const char *password, const ENetAddress &address)
        {
            copycubestr(game::connectPass, password);
        }

        void ConnectFail()
        {
            memset(game::connectPass, 0, sizeof(game::connectPass));
        }

        void GameDisconnect(bool cleanup)
        {
            if(game::remote) game::StopFollowing();
            //ignores.setsize(0);
            game::connected = game::remote = false;
            game::player1->ci.clientNumber = -1;
            if(editmode) toggleedit();
            sessionID = 0;
            game::masterMode = game::networking::protocol::MasterMode::Open;
            messages.setsize(0);
            messageReliable = false;
            messageClientNumber = -1;
            game::player1->respawn();
            game::player1->ci.lifeSequence = 0;
            game::player1->state = CS_ALIVE;
            game::player1->ci.privilege = game::networking::protocol::Priviliges::None;
            game::sendCRC = game::sendItemsToServer = false;
            game::demoPlayback = false;
            game::gamePaused = false;
            game::gameSpeed = 100;
            game::ClearClients(false);
            if(cleanup)
            {
                //game::nextMode =  game::gameMode = INT_MAX;
                game::gameMode = game::networking::GameMode::Lobby;;
                clientMap[0] = '\0';
            }
        }

        COMMANDN(say, toserver, "C", "Speak out to the players");

        void sayteam(char *text) { 
            if(!static_cast<int>(m_teammode) || !static_cast<int>(validteam(game::player1->ci.team))) return; 
            conoutf(game::networking::protocol::ConsoleMessage::Chat, "%s:%s %s", game::networking::GenerateClientColorName(&game::player1->ci), teamtextcode[game::player1->ci.team], text); 
            game::client::AddMessage(game::networking::protocol::Events::SayTeam, "rcs", game::player1->ci, text);
        }
        COMMAND(sayteam, "s");

        ICOMMAND(servcmd, "C", (char *cmd), AddMessage(game::networking::protocol::Events::ServerCommand, "rs", cmd));

        static void SendPosition(entities::classes::BaseClientEntity *d, packetbuf &q)
        {
            game::networking::putint(q, static_cast<int>(game::networking::protocol::Events::Position));
            game::networking::putuint(q, d->ci.clientNumber);
            // 3 bits phys state, 1 bit life sequence, 2 bits move, 2 bits strafe
            uchar physstate = d->physstate | ((d->ci.lifeSequence&1)<<3) | ((d->move&3)<<4) | ((d->strafe&3)<<6);
            q.put(physstate);
            ivec o = ivec(vec(d->o.x, d->o.y, d->o.z-d->eyeheight).mul(DMF));
            uint vel = min(int(d->vel.magnitude()*DVELF), 0xFFFF), fall = min(int(d->falling.magnitude()*DVELF), 0xFFFF);
            // 3 bits position, 1 bit velocity, 3 bits falling, 1 bit material, 1 bit crouching
            uint flags = 0;
            if(o.x < 0 || o.x > 0xFFFF) flags |= 1<<0;
            if(o.y < 0 || o.y > 0xFFFF) flags |= 1<<1;
            if(o.z < 0 || o.z > 0xFFFF) flags |= 1<<2;
            if(vel > 0xFF) flags |= 1<<3;
            if(fall > 0)
            {
                flags |= 1<<4;
                if(fall > 0xFF) flags |= 1<<5;
                if(d->falling.x || d->falling.y || d->falling.z > 0) flags |= 1<<6;
            }
            if((lookupmaterial(d->feetpos())&MATF_CLIP) == MAT_GAMECLIP) flags |= 1<<7;
            if(d->crouching < 0) flags |= 1<<8;
            game::networking::putuint(q, flags);
            loopk(3)
            {
                q.put(o[k]&0xFF);
                q.put((o[k]>>8)&0xFF);
                if(o[k] < 0 || o[k] > 0xFFFF) q.put((o[k]>>16)&0xFF);
            }
            uint dir = (d->yaw < 0 ? 360 + int(d->yaw)%360 : int(d->yaw)%360) + clamp(int(d->pitch+90), 0, 180)*360;
            q.put(dir&0xFF);
            q.put((dir>>8)&0xFF);
            q.put(clamp(int(d->roll+90), 0, 180));
            q.put(vel&0xFF);
            if(vel > 0xFF) q.put((vel>>8)&0xFF);
            float velyaw, velpitch;
            vectoyawpitch(d->vel, velyaw, velpitch);
            uint veldir = (velyaw < 0 ? 360 + int(velyaw)%360 : int(velyaw)%360) + clamp(int(velpitch+90), 0, 180)*360;
            q.put(veldir&0xFF);
            q.put((veldir>>8)&0xFF);
            if(fall > 0)
            {
                q.put(fall&0xFF);
                if(fall > 0xFF) q.put((fall>>8)&0xFF);
                if(d->falling.x || d->falling.y || d->falling.z > 0)
                {
                    float fallyaw, fallpitch;
                    vectoyawpitch(d->falling, fallyaw, fallpitch);
                    uint falldir = (fallyaw < 0 ? 360 + int(fallyaw)%360 : int(fallyaw)%360) + clamp(int(fallpitch+90), 0, 180)*360;
                    q.put(falldir&0xFF);
                    q.put((falldir>>8)&0xFF);
                }
            }
        }

        void SendPosition(entities::classes::BaseClientEntity *d, bool reliable)
        {
            if(d->state != CS_ALIVE && d->state != CS_EDITING) return;
            packetbuf q(100, reliable ? ENET_PACKET_FLAG_RELIABLE : 0);
            SendPosition(d, q);
            SendClientPacket(q.finalize(), 0);
        }

        void SendPositions()
        {
            loopv(players)
            {
                auto *d = dynamic_cast<entities::classes::BaseClientEntity*>(&game::players[i]);
                if((d == game::player1 || d->ai) && (d->state == CS_ALIVE || d->state == CS_EDITING))
                {
                    packetbuf q(100);
                    SendPosition(d, q);
                    for(int j = i+1; j < game::players.length(); j++)
                    {
                        auto *d = dynamic_cast<::entities::classes::BaseClientEntity*>(&game::players[j]);
                        if((d == game::player1 || d->ai) && (d->state == CS_ALIVE || d->state == CS_EDITING))
                            SendPosition(d, q);
                    }
                    SendClientPacket(q.finalize(), 0);
                    break;
                }
            }
        }

        void SendMessages()
        {
            packetbuf p(MAXTRANS);
            if(sendCRC)
            {
                p.reliable();
//                sendCRC = false;
                // const char *mname = GetClientMap();
                // networking::putint(p, networking::protocol::NetClientMessage::SendMap);
                // networking::sendcubestr(mname, p);
                // networking::putint(p, mname[0] ? GetMapCRC() : 0);
            }
            if(sendItemsToServer)
            {
                p.reliable();
                //entities::putitems(p);
                //if(cmode) cmode->senditems(p);
                sendItemsToServer = false;
            }
            if(messages.length())
            {
                p.put(messages.getbuf(), messages.length());
                messages.setsize(0);
                if(messageReliable) p.reliable();
                messageReliable = false;
                messageClientNumber = -1;
            }
            if(ftsClient.totalMilliseconds-lastping>250)
            {
                game::networking::putint(p, networking::protocol::NetClientMessage::Ping);
                game::networking::putint(p, ftsClient.totalMilliseconds);
                lastPing = ftsClient.totalMilliseconds;
            }
            SendClientPacket(p.finalize(), 1);
        }

        void c2sinfo(bool force) // send update to the server
        {
            static int lastupdate = -1000;
            if(ftsClient.totalMilliseconds - lastupdate < 40 && !force) return; // don't update faster than 30fps
            lastupdate = ftsClient.totalMilliseconds;
            SendPositions();
            SendMessages();
            FlushClient();
        }

        void SendIntro()
        {
            packetbuf p(MAXTRANS, ENET_PACKET_FLAG_RELIABLE);
            networking::putint(p, N_CONNECT);
            networking::sendcubestr(game::player1->name.c_str(), p);
            networking::putint(p, game::player1->model_idx);
            networking::putint(p, game::player1->0xff00ff);
            cubestr hash = "";
            if(connectPass[0])
            {
                game::server::hashpassword(game::player1->ci.clientNumber, sessionID, connectPass, hash);
                memset(connectPass, 0, sizeof(connectPass));
            }
            game::sendcubestr(hash.c_str(), p);
            authkey *a = servauth[0] && autoauth ? findauthkey(servauth) : NULL;
            if(a)
            {
                a->lastauth = lastmillis;
                sendcubestr(a->desc, p);
                sendcubestr(a->name, p);
            }
            else
            {
                sendcubestr("", p);
                sendcubestr("", p);
            }
            SendClientPacket(p.finalize(), 1);
        }

        void UpdateClientPositions(entities::BasePhysicalEntity  *d)
        {
            // update the position of other clients in the game in our world
            // don't care if he's in the scenery or other players,
            // just don't overlap with our client

            const float r = game::player1->radius+d->radius;
            const float dx = game::player1->o.x-d->o.x;
            const float dy = game::player1->o.y-d->o.y;
            const float dz = game::player1->o.z-d->o.z;
            const float rz = game::player1->aboveeye+d->eyeheight;
            const float fx = (float)fabs(dx), fy = (float)fabs(dy), fz = (float)fabs(dz);
            if(fx<r && fy<r && fz<rz && game::player1->state!=CS_SPECTATOR && d->state!=CS_DEAD)
            {
                if(fx<fy) d->o.y += dy<0 ? r-fy : -(r-fy);  // push aside
                else      d->o.x += dx<0 ? r-fx : -(r-fx);
            }
            int lagtime = ftsClient.totalMilliseconds-d->lastUpdate;
            if(lagtime)
            {
                if(d->state!=CS_SPAWNING && d->lastUpdate) d->plag = (d->plag*5+lagtime)/6;
                d->lastupdate = ftsClient.totalMilliseconds;
            }
        }

        void ParsePositions(ucharbuf &p)
        {
            int type;
            while(p.remaining()) switch(type = getint(p))
            {
                case N_DEMOPACKET: break;
                case N_POSITION:                        // position of another client
                {
                    int cn = getuint(p), physstate = p.get(), flags = getuint(p);
                    vec o, vel, falling;
                    float yaw, pitch, roll;
                    loopk(3)
                    {
                        int n = p.get(); n |= p.get()<<8; if(flags&(1<<k)) { n |= p.get()<<16; if(n&0x800000) n |= ~0U<<24; }
                        o[k] = n/DMF;
                    }
                    int dir = p.get(); dir |= p.get()<<8;
                    yaw = dir%360;
                    pitch = clamp(dir/360, 0, 180)-90;
                    roll = clamp(int(p.get()), 0, 180)-90;
                    int mag = p.get(); if(flags&(1<<3)) mag |= p.get()<<8;
                    dir = p.get(); dir |= p.get()<<8;
                    vecfromyawpitch(dir%360, clamp(dir/360, 0, 180)-90, 1, 0, vel);
                    vel.mul(mag/DVELF);
                    if(flags&(1<<4))
                    {
                        mag = p.get(); if(flags&(1<<5)) mag |= p.get()<<8;
                        if(flags&(1<<6))
                        {
                            dir = p.get(); dir |= p.get()<<8;
                            vecfromyawpitch(dir%360, clamp(dir/360, 0, 180)-90, 1, 0, falling);
                        }
                        else falling = vec(0, 0, -1);
                        falling.mul(mag/DVELF);
                    }
                    else falling = vec(0, 0, 0);
                    int seqcolor = (physstate>>3)&1;
                    entities::classes::BaseClientEntity *d = GetClient(cn);
                    if(!d || d->lifesequence < 0 || seqcolor!=(d->lifesequence&1) || d->state==CS_DEAD) continue;
                    float oldyaw = d->yaw, oldpitch = d->pitch, oldroll = d->roll;
                    d->yaw = yaw;
                    d->pitch = pitch;
                    d->roll = roll;
                    d->move = (physstate>>4)&2 ? -1 : (physstate>>4)&1;
                    d->strafe = (physstate>>6)&2 ? -1 : (physstate>>6)&1;
                    d->crouching = (flags&(1<<8))!=0 ? -1 : abs(d->crouching);
                    vec oldpos(d->o);
                    d->o = o;
                    d->o.z += d->eyeheight;
                    d->vel = vel;
                    d->falling = falling;
                    d->physstate = physstate&7;
                    UpdatePhysState(d);
                    UpdateClientPositions(d);
                    if(smoothmove && d->smoothmillis>=0 && oldpos.dist(d->o) < smoothdist)
                    {
                        d->newpos = d->o;
                        d->newyaw = d->yaw;
                        d->newpitch = d->pitch;
                        d->newroll = d->roll;
                        d->o = oldpos;
                        d->yaw = oldyaw;
                        d->pitch = oldpitch;
                        d->roll = oldroll;
                        (d->deltapos = oldpos).sub(d->newpos);
                        d->deltayaw = oldyaw - d->newyaw;
                        if(d->deltayaw > 180) d->deltayaw -= 360;
                        else if(d->deltayaw < -180) d->deltayaw += 360;
                        d->deltapitch = oldpitch - d->newpitch;
                        d->deltaroll = oldroll - d->newroll;
                        d->smoothmillis = ftsClient.lastMilliseconds;
                    }
                    else d->smoothmillis = 0;
                    if(d->state==CS_LAGGED || d->state==CS_SPAWNING) d->state = CS_ALIVE;
                    break;
                }

                case N_TELEPORT:
                {
                    int cn = getint(p), tp = getint(p), td = getint(p);
                    entities::classes::BaseClientEntity *d = GetClient(cn);
                    if(!d || d->lifesequence < 0 || d->state==CS_DEAD) continue;
                    entities::teleporteffects(d, tp, td, false);
                    break;
                }

                case N_JUMPPAD:
                {
                    int cn = getint(p), jp = getint(p);
                    entities::classes::BaseClientEntity *d = GetClient(cn);
                    if(!d || d->lifesequence < 0 || d->state==CS_DEAD) continue;
                    entities::jumppadeffects(d, jp, false);
                    break;
                }

                default:
                    neterr("type");
                    return;
            }
        }

        void ParseState(shared::entities::BaseEntity *d, ucharbuf &p, bool resume = false)
        {
            if(!d) { static shared::entities::BaseEntity dummy; d = &dummy; }
            if(resume)
            {
                if(d==player1) getint(p);
                else d->state = getint(p);
                d->frags = getint(p);
                d->flags = getint(p);
                d->deaths = getint(p);
            }
            d->lifesequence = getint(p);
            d->health = getint(p);
            d->maxhealth = getint(p);
            if(resume && d==player1)
            {
                getint(p);
                loopi(NUMGUNS) getint(p);
            }
            else
            {
                int gun = getint(p);
                d->gunselect = clamp(gun, 0, NUMGUNS-1);
                loopi(NUMGUNS) d->ammo[i] = getint(p);
            }
        }

        extern int deathscore;

        void ParseMessages(int cn, entities::classes::BaseEntity *d, ucharbuf &p)
        {
            static char text[MAXTRANS];
            int type;
            bool mapchanged = false, demopacket = false;

            while(p.remaining()) switch(type = getint(p))
            {
                case N_DEMOPACKET: demopacket = true; break;

                case N_SERVINFO:                   // welcome messsage from the server
                {
                    int mycn = getint(p), prot = getint(p);
                    if(prot!=PROTOCOL_VERSION)
                    {
                        conoutf(CON_ERROR, "you are using a different game protocol (you: %d, server: %d)", PROTOCOL_VERSION, prot);
                        disconnect();
                        return;
                    }
                    sessionID = getint(p);
                    game::player1->clientNumber = mycn;      // we are now connected
                    if(getint(p) > 0) conoutf("this server is password protected");
                    getcubestr(servDesc, p, sizeof(servDesc));
                    getcubestr(servAuth, p, sizeof(CleanupServer));
                    sendintro();
                    break;
                }

                case N_WELCOME:
                {
                    connected = true;
                    notifywelcome();
                    break;
                }

                case N_PAUSEGAME:
                {
                    bool val = getint(p) > 0;
                    int cn = getint(p);
                    entities::classes::BaseClientEntity *a = cn >= 0 ? GetClient(cn) : NULL;
                    if(!demopacket)
                    {
                        gamepaused = val;
                        game::player1->attacking = ACT_IDLE;
                    }
                    if(a) conoutf("%s %s the game", colorname(a), val ? "paused" : "resumed");
                    else conoutf("game is %s", val ? "paused" : "resumed");
                    break;
                }

                case N_GAMESPEED:
                {
                    int val = clamp(getint(p), 10, 1000), cn = getint(p);
                    entities::classes::BaseClientEntity *a = cn >= 0 ? GetClient(cn) : NULL;
                    if(!demopacket) gamespeed = val;
                    if(a) conoutf("%s set gamespeed to %d", colorname(a), val);
                    else conoutf("gamespeed is %d", val);
                    break;
                }

                case N_CLIENT:
                {
                    int cn = getint(p), len = getuint(p);
                    ucharbuf q = p.subbuf(len);
                    parsemessages(cn, GetClient(cn), q);
                    break;
                }

                case N_SOUND:
                    if(!d) return;
                    playsound(getint(p), &d->o);
                    break;

                case N_TEXT:
                {
                    if(!d) return;
                    getcubestr(text, p);
                    filtertext(text, text, true, true);
                    if(isignored(d->clientnum)) break;
                    if(d->state!=CS_DEAD && d->state!=CS_SPECTATOR)
                        particle_textcopy(d->abovehead(), text, PART_TEXT, 2000, 0x32FF64, 4.0f, -8);
                    conoutf(CON_CHAT, "%s:%s %s", colorname(d), teamtextcode[0], text);
                    break;
                }

                case N_SAYTEAM:
                {
                    int tcn = getint(p);
                    gameent *t = getclient(tcn);
                    getcubestr(text, p);
                    filtertext(text, text, true, true);
                    if(!t || isignored(t->clientnum)) break;
                    int team = validteam(t->team) ? t->team : 0;
                    if(t->state!=CS_DEAD && t->state!=CS_SPECTATOR)
                        particle_textcopy(t->abovehead(), text, PART_TEXT, 2000, teamtextcolor[team], 4.0f, -8);
                    conoutf(CON_TEAMCHAT, "%s:%s %s", colorname(t), teamtextcode[team], text);
                    break;
                }

                case N_MAPCHANGE:
                    getcubestr(text, p);
                    changemapserv(text, getint(p));
                    mapchanged = true;
                    if(getint(p)) entities::spawnitems();
                    else sendItemsToServer = false;
                    break;

                case N_FORCEDEATH:
                {
                    int cn = getint(p);
                    entities::classes::BaseClientEntity *d = cn==game::player1->ci.clientNumber ? game::player1 : NewClient(cn);
                    if(!d) break;
                    if(d==player1)
                    {
                        if(editmode) toggleedit();
                        if(deathscore) showscores(true);
                    }
                    else d->resetinterp();
                    d->state = CS_DEAD;
                    CheckFollow();
                    break;
                }

                // case N_ITEMLIST:
                // {
                //     int n;
                //     while((n = getint(p))>=0 && !p.overread())
                //     {
                //         if(mapchanged) entities::setspawn(n, true);
                //         getint(p); // type
                //     }
                //     break;
                // }

                case N_INITCLIENT:            // another client either connected or changed name/team
                {
                    int cn = getint(p);
                    gameent *d = newclient(cn);
                    if(!d)
                    {
                        getcubestr(text, p);
                        getcubestr(text, p);
                        getint(p);
                        getint(p);
                        break;
                    }
                    getcubestr(text, p);
                    filtertext(text, text, false, false, MAXNAMELEN);
                    if(!text[0]) copycubestr(text, "unnamed");
                    if(d->name[0])          // already connected
                    {
                        if(strcmp(d->name, text) && !isignored(d->clientnum))
                            conoutf("%s is now known as %s", colorname(d), colorname(d, text));
                    }
                    else                    // new client
                    {
                        conoutf("\f0join:\f7 %s", colorname(d, text));
                        if(needclipboard >= 0) needclipboard++;
                    }
                    copycubestr(d->name, text, MAXNAMELEN+1);
                    d->team = getint(p);
                    if(!validteam(d->team)) d->team = 0;
                    d->playermodel = getint(p);
                    d->playercolor = getint(p);
                    break;
                }

                case N_SWITCHNAME:
                    getcubestr(text, p);
                    if(d)
                    {
                        filtertext(text, text, false, false, MAXNAMELEN);
                        if(!text[0]) copycubestr(text, "unnamed");
                        if(strcmp(text, d->name))
                        {
                            if(!isignored(d->clientnum)) conoutf("%s is now known as %s", colorname(d), colorname(d, text));
                            copycubestr(d->name, text, MAXNAMELEN+1);
                        }
                    }
                    break;

                case N_SWITCHMODEL:
                {
                    int model = getint(p);
                    if(d)
                    {
                        d->playermodel = model;
                        if(d->ragdoll) cleanragdoll(d);
                    }
                    break;
                }

                case N_SWITCHCOLOR:
                {
                    int color = getint(p);
                    if(d) d->playercolor = color;
                    break;
                }

                case N_CDIS:
                    ClientDIsConnected(getint(p));
                    break;

                case N_SPAWN:
                {
                    if(d)
                    {
                        if(d->state==CS_DEAD && d->lastpain) saveragdoll(d);
                        d->respawn();
                    }
                    parsestate(d, p);
                    if(!d) break;
                    d->state = CS_SPAWNING;
                    if(d == followingplayer()) lasthit = 0;
                    checkfollow();
                    break;
                }

                case N_SPAWNSTATE:
                {
                    int scn = getint(p);
                    entities::classes::BaseClientEntity *s = GetClient(scn);
                    if(!s) { ParseState(NULL, p); break; }
                    if(s->state==CS_DEAD && s->lastpain) saveragdoll(s);
                    if(s==player1)
                    {
                        if(editmode) toggleedit();
                    }
                    s->respawn();
                    ParseState(s, p);
                    s->state = CS_ALIVE;
                    //if(cmode) cmode->pickspawn(s);
                    else findplayerspawn(s, -1, m_teammode ? s->team : 0);
                    if(s == player1)
                    {
                        showscores(false);
                        lasthit = 0;
                    }
                    //if(cmode) cmode->respawned(s);
                    //ai::spawned(s);
                    checkfollow();
                    addmsg(N_SPAWN, "rcii", s, s->lifesequence, s->gunselect);
                    break;
                }

        //         case N_SHOTFX:
        //         {
        //             int scn = getint(p), atk = getint(p), id = getint(p);
        //             vec from, to;
        //             loopk(3) from[k] = getint(p)/DMF;
        //             loopk(3) to[k] = getint(p)/DMF;
        //             gameent *s = getclient(scn);
        //             if(!s || !validatk(atk)) break;
        //             int gun = attacks[atk].gun;
        //             s->gunselect = gun;
        //             s->ammo[gun] -= attacks[atk].use;
        //             s->gunwait = attacks[atk].attackdelay;
        //             int prevaction = s->lastaction;
        //             s->lastaction = lastmillis;
        //             s->lastattack = atk;
        //             shoteffects(atk, from, to, s, false, id, prevaction);
        //             break;
        //         }

        //         case N_EXPLODEFX:
        //         {
        //             int ecn = getint(p), atk = getint(p), id = getint(p);
        //             gameent *e = getclient(ecn);
        //             if(!e || !validatk(atk)) break;
        //             explodeeffects(atk, e, false, id);
        //             break;
        //         }
        //         case N_DAMAGE:
        //         {
        //             int tcn = getint(p),
        //                 acn = getint(p),
        //                 damage = getint(p),
        //                 health = getint(p);
        //             gameent *target = getclient(tcn),
        //                     *actor = getclient(acn);
        //             if(!target || !actor) break;
        //             target->health = health;
        //             if(target->state == CS_ALIVE && actor != player1) target->lastpain = lastmillis;
        //             damaged(damage, target, actor, false);
        //             break;
        //         }

        //         case N_HITPUSH:
        //         {
        //             int tcn = getint(p), atk = getint(p), damage = getint(p);
        //             gameent *target = getclient(tcn);
        //             vec dir;
        //             loopk(3) dir[k] = getint(p)/DNF;
        //             if(!target || !validatk(atk)) break;
        //             target->hitpush(damage * (target->health<=0 ? deadpush : 1), dir, NULL, atk);
        //             break;
        //         }

        //         case N_DIED:
        //         {
        //             int vcn = getint(p), acn = getint(p), frags = getint(p), tfrags = getint(p);
        //             gameent *victim = getclient(vcn),
        //                     *actor = getclient(acn);
        //             if(!actor) break;
        //             actor->frags = frags;
        //             if(m_teammode) setteaminfo(actor->team, tfrags);
        // #if 0
        //             if(actor!=player1 && (!cmode || !cmode->hidefrags()))
        //                 particle_textcopy(actor->abovehead(), tempformatcubestr("%d", actor->frags), PART_TEXT, 2000, 0x32FF64, 4.0f, -8);
        // #endif
        //             if(!victim) break;
        //             killed(victim, actor);
        //             break;
        //         }

        //         case N_TEAMINFO:
        //             loopi(MAXTEAMS)
        //             {
        //                 int frags = getint(p);
        //                 if(m_teammode) setteaminfo(1+i, frags);
        //             }
        //             break;

        //         case N_GUNSELECT:
        //         {
        //             if(!d) return;
        //             int gun = getint(p);
        //             if(!validgun(gun)) return;
        //             d->gunselect = gun;
        //             playsound(S_WEAPLOAD, &d->o);
        //             break;
        //         }

        //         case N_TAUNT:
        //         {
        //             if(!d) return;
        //             d->lasttaunt = lastmillis;
        //             break;
        //         }

        //         case N_RESUME:
                {
                    for(;;)
                    {
                        int cn = getint(p);
                        if(p.overread() || cn<0) break;
                        gameent *d = (cn == player1->clientnum ? player1 : newclient(cn));
                        parsestate(d, p, true);
                    }
                    break;
                }

                // case N_ITEMSPAWN:
                // {
                //     int i = getint(p);
                //     if(!entities::ents.inrange(i)) break;
                //     entities::setspawn(i, true);
                //     ai::itemspawned(i);
                //     playsound(S_ITEMSPAWN, &entities::ents[i]->o, NULL, 0, 0, 0, -1, 0, 1500);
                //     #if 0
                //     const char *name = entities::itemname(i);
                //     if(name) particle_text(entities::ents[i]->o, name, PART_TEXT, 2000, 0x32FF64, 4.0f, -8);
                //     #endif
                //     int icon = entities::itemicon(i);
                //     if(icon >= 0) particle_icon(vec(0.0f, 0.0f, 4.0f).add(entities::ents[i]->o), icon%4, icon/4, PART_HUD_ICON, 2000, 0xFFFFFF, 2.0f, -8);
                //     break;
                // }

                // case N_ITEMACC:            // server acknowledges that I picked up this item
                // {
                //     int i = getint(p), cn = getint(p);
                //     gameent *d = getclient(cn);
                //     entities::pickupeffects(i, d);
                //     break;
                // }

                // case N_CLIPBOARD:
                // {
                //     int cn = getint(p), unpacklen = getint(p), packlen = getint(p);
                //     gameent *d = getclient(cn);
                //     ucharbuf q = p.subbuf(max(packlen, 0));
                //     if(d) unpackeditinfo(d->edit, q.buf, q.maxlen, unpacklen);
                //     break;
                // }
                // case N_UNDO:
                // case N_REDO:
                // {
                //     int cn = getint(p), unpacklen = getint(p), packlen = getint(p);
                //     gameent *d = getclient(cn);
                //     ucharbuf q = p.subbuf(max(packlen, 0));
                //     if(d) unpackundo(q.buf, q.maxlen, unpacklen);
                //     break;
                // }

                // case N_EDITF:              // coop editing messages
                // case N_EDITT:
                // case N_EDITM:
                // case N_FLIP:
                // case N_COPY:
                // case N_PASTE:
                // case N_ROTATE:
                // case N_REPLACE:
                // case N_DELCUBE:
                // case N_EDITVSLOT:
                // {
                //     if(!d) return;
                //     selinfo sel;
                //     sel.o.x = getint(p); sel.o.y = getint(p); sel.o.z = getint(p);
                //     sel.s.x = getint(p); sel.s.y = getint(p); sel.s.z = getint(p);
                //     sel.grid = getint(p); sel.orient = getint(p);
                //     sel.cx = getint(p); sel.cxs = getint(p); sel.cy = getint(p), sel.cys = getint(p);
                //     sel.corner = getint(p);
                //     switch(type)
                //     {
                //         case N_EDITF: { int dir = getint(p), mode = getint(p); if(sel.validate()) mpeditface(dir, mode, sel, false); break; }
                //         case N_EDITT:
                //         {
                //             int tex = getint(p),
                //                 allfaces = getint(p);
                //             if(p.remaining() < 2) return;
                //             int extra = lilswap(*(const ushort *)p.pad(2));
                //             if(p.remaining() < extra) return;
                //             ucharbuf ebuf = p.subbuf(extra);
                //             if(sel.validate()) mpedittex(tex, allfaces, sel, ebuf);
                //             break;
                //         }
                //         case N_EDITM: { int mat = getint(p), filter = getint(p); if(sel.validate()) mpeditmat(mat, filter, sel, false); break; }
                //         case N_FLIP: if(sel.validate()) mpflip(sel, false); break;
                //         case N_COPY: if(d && sel.validate()) mpcopy(d->edit, sel, false); break;
                //         case N_PASTE: if(d && sel.validate()) mppaste(d->edit, sel, false); break;
                //         case N_ROTATE: { int dir = getint(p); if(sel.validate()) mprotate(dir, sel, false); break; }
                //         case N_REPLACE:
                //         {
                //             int oldtex = getint(p),
                //                 newtex = getint(p),
                //                 insel = getint(p);
                //             if(p.remaining() < 2) return;
                //             int extra = lilswap(*(const ushort *)p.pad(2));
                //             if(p.remaining() < extra) return;
                //             ucharbuf ebuf = p.subbuf(extra);
                //             if(sel.validate()) mpreplacetex(oldtex, newtex, insel>0, sel, ebuf);
                //             break;
                //         }
                //         case N_DELCUBE: if(sel.validate()) mpdelcube(sel, false); break;
                //         case N_EDITVSLOT:
                //         {
                //             int delta = getint(p),
                //                 allfaces = getint(p);
                //             if(p.remaining() < 2) return;
                //             int extra = lilswap(*(const ushort *)p.pad(2));
                //             if(p.remaining() < extra) return;
                //             ucharbuf ebuf = p.subbuf(extra);
                //             if(sel.validate()) mpeditvslot(delta, allfaces, sel, ebuf);
                //             break;
                //         }
                //     }
                //     break;
                // }
                // case N_REMIP:
                //     if(!d) return;
                //     conoutf("%s remipped", colorname(d));
                //     mpremip(false);
                //     break;
                // case N_CALCLIGHT:
                //     if(!d) return;
                //     conoutf("%s calced lights", colorname(d));
                //     mpcalclight(false);
                //     break;
                // case N_EDITENT:            // coop edit of ent
                // {
                //     if(!d) return;
                //     int i = getint(p);
                //     float x = getint(p)/DMF, y = getint(p)/DMF, z = getint(p)/DMF;
                //     int type = getint(p);
                //     int attr1 = getint(p), attr2 = getint(p), attr3 = getint(p), attr4 = getint(p), attr5 = getint(p);

                //     mpeditent(i, vec(x, y, z), type, attr1, attr2, attr3, attr4, attr5, false);
                //     break;
                // }
                // case N_EDITVAR:
                // {
                //     if(!d) return;
                //     int type = getint(p);
                //     getcubestr(text, p);
                //     cubestr name;
                //     filtertext(name, text, false);
                //     ident *id = getident(name);
                //     switch(type)
                //     {
                //         case ID_VAR:
                //         {
                //             int val = getint(p);
                //             if(id && id->flags&IDF_OVERRIDE && !(id->flags&IDF_READONLY)) setvar(name, val);
                //             break;
                //         }
                //         case ID_FVAR:
                //         {
                //             float val = getfloat(p);
                //             if(id && id->flags&IDF_OVERRIDE && !(id->flags&IDF_READONLY)) setfvar(name, val);
                //             break;
                //         }
                //         case ID_SVAR:
                //         {
                //             getcubestr(text, p);
                //             if(id && id->flags&IDF_OVERRIDE && !(id->flags&IDF_READONLY)) setsvar(name, text);
                //             break;
                //         }
                //     }
                //     printvar(d, id);
                //     break;
                // }

                // case N_PONG:
                //     addmsg(N_CLIENTPING, "i", player1->ping = (player1->ping*5+ftsClient.totalMilliseconds-getint(p))/6);
                //     break;

                // case N_CLIENTPING:
                //     if(!d) return;
                //     d->ping = getint(p);
                //     break;

                // case N_TIMEUP:
                //     timeupdate(getint(p));
                //     break;

                case N_SERVMSG:
                    getcubestr(text, p);
                    conoutf("%s", text);
                    break;

                case N_SENDDEMOLIST:
                {
                    int demos = getint(p);
                    if(demos <= 0) conoutf("no demos available");
                    else loopi(demos)
                    {
                        getcubestr(text, p);
                        if(p.overread()) break;
                        conoutf("%d. %s", i+1, text);
                    }
                    break;
                }

                case N_DEMOPLAYBACK:
                {
                    int on = getint(p);
                    if(on) game::player1->state = CS_SPECTATOR;
                    else game::ClearClients();
                    game::demoPlayback = on!=0;
                    game::player1->ci.clientNumber = getint(p);
                    game::gamePaused = false;
                    game::CheckFollow();
                    execident(on ? "demostart" : "demoend");
                    break;
                }

                case N_CURRENTMASTER:
                {
                    int mm = getint(p), mn;
                    loopv(game::players) game::players[i]->ci.privilege = game::networking::protocol::Priviliges::Admin;
                    while((mn = getint(p))>=0 && !p.overread())
                    {
                        entities::classes::BaseClientEntity *m = mn == game::player1->ci.clientNumber ? dynamic_cast<entities::classes::Player>(game::player1) : NewClient(mn);
                        int priv = getint(p);
                        if(m) m->ci.privilege = priv;
                    }
                    if(mm != game::masterMode)
                    {
                        game::masterMode = mm;
                        conoutf("mastermode is %s (%d)", server::mastermodename(mastermode), mastermode);
                    }
                    break;
                }

                case N_MASTERMODE:
                {
                    mastermode = getint(p);
                    conoutf("mastermode is %s (%d)", server::mastermodename(mastermode), mastermode);
                    break;
                }

                case N_EDITMODE:
                {
                    int val = getint(p);
                    if(!d) break;
                    if(val)
                    {
                        d->editstate = d->state;
                        d->state = CS_EDITING;
                    }
                    else
                    {
                        d->state = d->editstate;
                        if(d->state==CS_DEAD) deathstate(d, true);
                    }
                    CheckFollow();
                    break;
                }

                case N_SPECTATOR:
                {
                    int sn = getint(p), val = getint(p);
                    entities::classes::BaseClientEntity *s;
                    if(sn==game::player1->ci.clientNumber)
                    {
                        s = dynamic_cast<entities::classes::Player>(game::player1);
                        if(val && remote && !player1->privilege) senditemstoserver = false;
                    }
                    else s = newclient(sn);
                    if(!s) return;
                    if(val)
                    {
                        if(s==player1)
                        {
                            if(editmode) toggleedit();
                            if(s->state==CS_DEAD) showscores(false);
                            disablezoom();
                        }
                        s->state = CS_SPECTATOR;
                    }
                    else if(s->state==CS_SPECTATOR) deathstate(s, true);
                    checkfollow();
                    break;
                }

                case N_NEWMAP:
                {
                    int size = getint(p);
                    if(size>=0) emptymap(size, true, NULL);
                    else enlargemap(true);
                    if(d && d!=player1)
                    {
                        int newsize = 0;
                        while(1<<newsize < getworldsize()) newsize++;
                        conoutf(size>=0 ? "%s started a new map of size %d" : "%s enlarged the map to size %d", colorname(d), newsize);
                    }
                    break;
                }

                case N_REQAUTH:
                {
                    getcubestr(text, p);
                    if(autoauth && text[0] && tryauth(text)) conoutf("server requested authkey \"%s\"", text);
                    break;
                }

                case N_AUTHCHAL:
                {
                    getcubestr(text, p);
                    authkey *a = findauthkey(text);
                    uint id = (uint)getint(p);
                    getcubestr(text, p);
                    if(a && a->lastauth &&  ftsClient.lastMilliseconds - a->lastauth < 60*1000)
                    {
                        vector<char> buf;
                        answerchallenge(a->key, text, buf);
                        //conoutf(CON_DEBUG, "answering %u, challenge %s with %s", id, text, buf.getbuf());
                        packetbuf p(MAXTRANS, ENET_PACKET_FLAG_RELIABLE);
                        putint(p, N_AUTHANS);
                        sendcubestr(a->desc, p);
                        putint(p, id);
                        sendcubestr(buf.getbuf(), p);
                        SendClientPacket(p.finalize(), 1);
                    }
                    break;
                }

                case N_INITAI:
                {
                    int bn = getint(p), on = getint(p), at = getint(p), sk = clamp(getint(p), 1, 101), pm = getint(p), col = getint(p), team = getint(p);
                    cubestr name;
                    getcubestr(text, p);
                    filtertext(name, text, false, false, MAXNAMELEN);
                    entities::classes::BaseClientEntity *b = NewClient(bn);
                    if(!b) break;
                    ai::init(b, at, on, sk, bn, pm, col, name, team);
                    break;
                }

                case N_SERVCMD:
                    getcubestr(text, p);
                    break;

                default:
                    neterr("type", cn < 0);
                    return;
            }
        }

        void ReceiveFile(packetbuf &p)
        {
            int type;
            while(p.remaining()) switch(type = getint(p))
            {
                case N_DEMOPACKET: return;
                case N_SENDDEMO:
                {
                    defformatcubestr(fname, "%d.dmo", lastmillis);
                    stream *demo = openrawfile(fname, "wb");
                    if(!demo) return;
                    conoutf("received demo \"%s\"", fname);
                    ucharbuf b = p.subbuf(p.remaining());
                    demo->write(b.buf, b.maxlen);
                    delete demo;
                    break;
                }

                case N_SENDMAP:
                {
                    if(!m_edit) return;
                    cubestr oldname;
                    copycubestr(oldname, getclientmap());
                    defformatcubestr(mname, "getmap_%d", lastmillis);
                    defformatcubestr(fname, "media/map/%s.ogz", mname);
                    stream *map = openrawfile(path(fname), "wb");
                    if(!map) return;
                    conoutf("received map");
                    ucharbuf b = p.subbuf(p.remaining());
                    map->write(b.buf, b.maxlen);
                    delete map;
                    if(load_world(mname, oldname[0] ? oldname : NULL))
                        entities::spawnitems(true);
                    remove(findfile(fname, "rb"));
                    break;
                }
            }
        }

        void ParsePacketClient(int chan, packetbuf &p)   // processes any updates from the server
        {
            if(p.packet->flags&ENET_PACKET_FLAG_UNSEQUENCED) return;
            switch(chan)
            {
                case 0:
                    ParsePositions(p);
                    break;

                case 1:
                    ParseMessages(-1, NULL, p);
                    break;

                case 2:
                    ReceiveFile(p);
                    break;
            }
        }

        void getmap()
        {
            if(!m_edit) { conoutf(CON_ERROR, "\"getmap\" only works in edit mode"); return; }
            conoutf("getting map...");
            addmsg(N_GETMAP, "r");
        }
        COMMAND(getmap, "");

        void sendmap()
        {
            if(!m_edit || (game::player1->state==CS_SPECTATOR && remote && !game::player1->privilege)) { conoutf(CON_ERROR, "\"sendmap\" only works in coop edit mode"); return; }
            conoutf("sending map...");
            defformatcubestr(mname, "sendmap_%d", ftsClient.lastMilliseconds);
            save_world(mname, true);
            defformatcubestr(fname, "media/map/%s.ogz", mname);
            stream *map = openrawfile(path(fname), "rb");
            if(map)
            {
                stream::offset len = map->size();
                if(len > 4*1024*1024) conoutf(CON_ERROR, "map is too large");
                else if(len <= 0) conoutf(CON_ERROR, "could not read map");
                else
                {
                    sendfile(-1, 2, map);
                    if(needclipboard >= 0) needclipboard++;
                }
                delete map;
            }
            else conoutf(CON_ERROR, "could not read map");
            remove(findfile(fname, "rb"));
        }
        COMMAND(sendmap, "");
    } // client
} // game