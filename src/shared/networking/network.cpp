#include "cube.h"
#include "ents.h"

#include "game/game.h"
#include "game/server/server.h"
#include "game/client/client.h"

#include "shared/networking/cl_sv.h"
#include "shared/networking/network.h"
#include "shared/networking/frametimestate.h"
#include "shared/networking/protocol.h"

#include "shared/entities/animinfo.h"
#include "shared/entities/coreentity.h"
#include "shared/entities/baseentity.h"
#include "shared/entities/basephysicalentity.h"
#include "shared/entities/basedynamicentity.h"
#include "shared/entities/basecliententity.h"

namespace game { namespace networking { 
    game::networking::ClientInfo *FindAuth(uint id)
    {
        loopv(clients) if(clients[i]->authReq == id) return clients[i];
        return NULL;
    }

    void authFailed(game::networking::ServerClientInfo *ci)
    {
        if(!ci) return;
        ci->CleanAuth();
        if(ci->connectAuth) Disconnect_Client(ci->clientNumber, ci->connectAuth);
    }

    void AuthFailed(uint id)
    {
        AuthFailed(FindAuth(id));
    }

    void AuthSucceeded(uint id)
    {
        game::networking::server::ClientInfo *ci = FindAuth(id);
        if(!ci) return;
        ci->CleanAuth(ci->connectAuth!=0);
        if(ci->connectAuth) Connected(ci);
        if(ci->authKickVictim >= 0)
        {
            if(SetMaster(ci, true, "", ci->authName, NULL, protocol::Priviliges::Auth, false, true))
                TryKick(ci, ci->authKickVictim, ci->authKickReason, ci->authName, NULL, Priviliges::Auth);
            ci->CleanAuthKick();
        }
        else SetMaster(ci, true, "", ci->authName, NULL, game::networking::Priviliges::Auth);
    }

    void AuthChallenged(uint id, const char *val, const char *desc = "")
    {
        ServerClientInfo *ci = FindAuth(id);
        if(!ci) return;
        sendf(ci->clientNumber, 1, "risis", protocol::Events::AuthChallenge, desc, id, val);
    }

    uint nextAuthReq = 0;

    bool TryAuth(game::networking::ClientInfo *ci, const char *user, const char *desc)
    {
        ci->CleanAuth();
        if(!nextAuthReq) nextAuthReq = 1;
        ci->authreq = nextAuthReq++;
        filtertext(ci->authName, user, false, false, 100);
        copycubestr(ci->authDesc, desc);
        if(ci->authdesc[0])
        {
            UserInfo *u = users.access(UserKey(ci->authName, ci->authDesc));
            if(u)
            {
                uint seed[3] = { ::hthash(serverAuth) + detrnd(size_t(ci) + size_t(user) + size_t(desc), 0x10000), uint(ftsClient.totalMilliseconds), randomMT() };
                vector<char> buf;
                ci->authChallenge = genchallenge(u->pubkey, seed, sizeof(seed), buf);
                sendf(ci->clientNumber, 1, "risis", protocol::Events::AuthChallenge, desc, ci->authReq, buf.getbuf());
            }
            else ci->CleanAuth();
        }
        else if(!RequestMasterf("reqauth %u %s\n", ci->authReq, ci->authName))
        {
            ci->CleanAuth();
            sendf(ci->clientNumber, 1, "ris", protocol::Events::ServerMessage, "not connected to authentication server");
        }
        if(ci->authReq) return true;
        if(ci->connectAuth) Disconnect_Client(ci->clientNum, ci->connectAuth);
        return false;
    }

    bool AnswerChallenge(ServerClientInfo *ci, uint id, char *val, const char *desc)
    {
        if(ci->authReq != id || strcmp(ci->authDesc, desc))
        {
            ci->CleanAuth();
            return !ci->connectedAuth;
        }
        for(char *s = val; *s; s++)
        {
            if(!isxdigit(*s)) { *s = '\0'; break; }
        }
        if(desc[0])
        {
            if(ci->authChallenge && CheckChallenge(val, ci->authChallenge))
            {
                UserInfo *u = users.access(userkey(ci->authName, ci->authDesc));
                if(u)
                {
                    if(ci->connectAuth) Connected(ci);
                    if(ci->authKickVictim >= 0)
                    {
                        if(SetMaster(ci, true, "", ci->authName, ci->authDesc, u->privilege, false, true))
                            TryKick(ci, ci->authkickvictim, ci->authKickReason, ci->authName, ci->authDesc, u->privilege);
                    }
                    else SetMaster(ci, true, "", ci->authName, ci->authDesc, u->privilege);
                }
            }
            ci->CleanAuth();
        }
        else if(!RequestMasterf("confauth %u %s\n", id, val))
        {
            ci->CleanAuth();
            sendf(ci->clientNumber, 1, "ris", NetClientMessage::Disconnect, "not connected to authentication server");
        }
        return ci->authReq || !ci->connectAuth;
    }

    bool DuplicateName(networking::ClientInfo *ci, const std::string &name)
    {
        if(!name) name = ci->name;
        loopv(clients) if(clients[i]!= ci && name != std::string(clients[i]->name))) return true;
        return false;
    }
}; // networking
}; // game