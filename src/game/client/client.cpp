#include "engine/engine.h"

#include "shared/cube.h"
#include "shared/command.h"
#include "shared/utils/cubestr.h"

#include "shared/networking/cl_sv.h"
#include "shared/networking/network.h"
#include "shared/networking/cl_frametimestate.h"
#include "shared/networking/sv_frametimestate.h"
#include "shared/networking/protocol.h"

#include "shared/entities/coreentity.h"
#include "shared/entities/baseentity.h"
#include "shared/entities/basedynamicentity.h"
#include "shared/entities/basecliententity.h"

#include "game/game.h"
#include "game/client/client.h"
#include "game/client/authorizationkey.h"

#include "game/entities.h"
#include "game/entities/player.h"

namespace game {
    namespace client {

        // Client Game State variables, or so, I believe.
        // These can be put in ClientGameState struct, game::client::clState would be global
        bool senditemstoserver = false, sendcrc = false; // after a map change, since server doesn't have map data
        int lastping = 0;

        bool connected = false;
        bool remote = false;
        bool demoplayback = false;
        bool gamepaused = false;
        int sessionid = 0;

        shared::network::protocol::MasterMode mastermode = shared::network::protocol::MasterMode::Open;
        int gamespeed = 100;
        
        //
        // ServerDescription - TODO: Struct, std::stringify
        //
        struct ServAuthentication {
            cubestr servdesc = "";
            cubestr servauth = "";
            cubestr connectpass = "";
        };
        ServAuthentication svAuthentication;

        VARP(deadpush, 1, 2, 20);

        void SwitchName(const char *name) {
            char nickname[MAX_CLIENT_NAME_LENGTH]; // Temp method to avoid filtertext std::string issues.
            FilterText(nickname, name, false, false, MAX_CLIENT_NAME_LENGTH);
            game::clPlayer->clientInformation.nickname = nickname;
            if(game::clPlayer->clientInformation.nickname.empty())
                game::clPlayer->clientInformation.nickname = "n00bnamed";
            AddMessages(shared::network::protocol::Messages::SwitchName, "rs", game::clPlayer->clientInformation.nickname.c_str());
        }
        void PrintName() {
            conoutf("Your name is: %s", game::client::GenerateClientColorName(game::clPlayer, game::clPlayer->clientInformation.nickname));
        }
        // // Returns a coloured string of a name.
        const char *GenerateClientColorName(entities::classes::BaseEntity *c, const std::string &nick) {
            entities::classes::BaseClientEntity *ce = dynamic_cast<entities::classes::BaseClientEntity*>(c);
            if (!ce) {
                conoutf(CON_WARN, "%s", "Invalid pointer reference to ClientInfo *ci: == %d", (void*)&ce->clientInformation);
                return "invalid_ref";
            }

            static cubestr cname[3];
            static int colorIndex = 0;
            colorIndex = (colorIndex+1)%3;

            std::string nickname = "unnamed_#" + std::to_string(colorIndex);
            if(nick.size() < 260) { // Stay below CubeStr its max value.
                if (nick.empty()) {
                    nickname = std::string(ce->clientInformation.nickname).substr(0, 32);
                } else {
                    nickname = "unnamed_#" + std::to_string(colorIndex);
                }
            }

            if(!nick.empty() && !shared::network::HasClientDuplicateName(ce, nick))//&& ce->state.aitype == 0)  // It used to be that.
                return nick.c_str();
            
            // Generate colour based on type of Client and client number.
            // WatIsDeze: TODO: This is ancient code. ci->state.aitype??? Not now, maybe later.
            formatcubestr(cname[colorIndex], "%s \fs\f5[%d]\fr", nick.c_str(), ce->clientNumber);
            return cname[colorIndex];
        }
        ICOMMAND(name, "sN", (char *s, int *numargs),
        {
            if(*numargs > 0) SwitchName(s);
            else if(!*numargs) PrintName();
            //else cubestrret(ClientColorName(game::clPlayer->nickname));
        }, "Changes the player's name.");
        ICOMMAND(getname, "", (), {cubestrret((char*)game::clPlayer->clientInformation.nickname.c_str()); }, "Returns the player's name.");

        void SendMapInfo()
        {
            if(!connected) return;
            sendcrc = true;
            if(game::clPlayer->state!=CS_SPECTATOR || static_cast<bool>(game::clPlayer->clientInformation.privilege) || !remote) senditemstoserver = true;
        }

        void WriteClientInfo(stream *f)
        {
            f->printf("name %s\n", escapecubestr(clPlayer->clientInformation.nickname.c_str()));
        }

        //
        // "Collect all the client to server(c2s) messages conveniently in a struct. Cleaner vs
        // the original code. It actually has c2s in some of its func/var names. Wwhich I find 
        // to be a mutulation for a variable name but whatever.  I'll stop ranting, and get back
        // to programming.
        //
        // Wait, be honest, so here I am: "I guess, it is readable and keeps it related to its past.""
        // 
        // Yeah, I got a bit emotional and all that above there." -- WatIsDeze : Mike.
        //
        struct CL2SVMessages {
            vector<uchar> messages;    
            int messageClientNumber = -1;
            int messageReliable = false;
        }; 
        CL2SVMessages Cl2SvMessages;

        // TODO: Variadic templates! Screw the old vararg method, This allows for so much more! :) <3 -- WatIsDeze : Mike        
        bool AddMessages(shared::network::protocol::Messages type, const char * fmt, ...) {
            if(!connected) 
                return false;

            static uchar buf[MAXTRANS];
            ucharbuf p(buf, sizeof(buf)); // Buffer mang, let's do this.
            shared::network::PutMessage(p, type); // Put the message cuz we do this shit.
            int numi = 1; // Number of integer variables (lol, they do not resemble humans) given.
            int numf = 0; // Number of FLOAT FUCKS GIVEN.
            int nums = 0; // Number of strings,
            int mcn = -1; // Multiplayer Client Number(It is but..? Or Master client number? This code supposed has had to be readable.)
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
                        entities::classes::BaseClientEntity *d = dynamic_cast<entities::classes::BaseClientEntity*>(
                            va_arg(args, entities::classes::BaseClientEntity *)
                        );

                        mcn = !d || d == clPlayer ? -1 : d->clientInformation.clientNumber;
                        break;
                    }
                    case 'v':
                    {
                        int n = va_arg(args, int);
                        shared::network::protocol::Messages *v = va_arg(args, shared::network::protocol::Messages *);
                        loopi(n) shared::network::PutMessage(p, v[i]);
                        numi += n;
                        break;
                    }

                    case 'i':
                    {
                        int n = isdigit(*fmt) ? *fmt++-'0' : 1;
                        loopi(n) shared::network::PutMessage(p, va_arg(args, shared::network::protocol::Messages));
                        numi += n;
                        break;
                    }
                    case 'f':
                    {
                        int n = isdigit(*fmt) ? *fmt++-'0' : 1;
                        loopi(n) shared::network::PutFloat(p, (float)va_arg(args, double));
                        numf += n;
                        break;
                    }
                    case 's': shared::network::SendCubeStr(va_arg(args, const char *), p); nums++; break;
                }
                va_end(args);
            }
            int num = nums || numf ? 0 : numi, messageSize = shared::network::protocol::MessageSizeLookup(type);
            if(messageSize && num != messageSize) { fatal("Inconsistent msg size for %d (%d != %d)", static_cast<int>(type), num, messageSize); }
            if(reliable) Cl2SvMessages.messageReliable = true;
            if(mcn != Cl2SvMessages.messageClientNumber)
            {
                static uchar mbuf[16];
                ucharbuf m(mbuf, sizeof(mbuf));
                shared::network::PutMessage(m, shared::network::protocol::Messages::FromAI);
                shared::network::PutInt(m, mcn);
                Cl2SvMessages.messages.put(mbuf, m.length());
                Cl2SvMessages.messageClientNumber = mcn;
            }
            Cl2SvMessages.messages.put(buf, p.length());
            return true;
        }
    };
};