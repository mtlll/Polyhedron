#include "cube.h"
#include "ents.h"

#include "engine/engine.h"
#include "engine/server/server.h"

#include "game/game.h"
#include "game/server/server.h"

#include "shared/networking/cl_sv.h"
#include "shared/networking/network.h"
#include "shared/networking/cl_frametimestate.h"
#include "shared/networking/sv_frametimestate.h"
#include "shared/networking/protocol.h"

#include "shared/entities/animinfo.h"
#include "shared/entities/coreentity.h"
#include "shared/entities/baseentity.h"
#include "shared/entities/basephysicalentity.h"
#include "shared/entities/basedynamicentity.h"
#include "shared/entities/basecliententity.h"

namespace game {
        namespace network {
        using game::server::svClients;
        hashset<shared::network::UserInfo> users;

        shared::network::ClientInfo *GetServDynEntInfoPtr(shared::network::ServerDynamicEnt *sde) {
            if (!sde) {
                return NULL;
            } else {
                shared::network::ClientInfo *ci = (shared::network::ClientInfo*)(sde->info);
                return ci;
            }
        }
        
        shared::network::ClientInfo *FindAuth(uint id)
        {
            loopv(svClients.clients) { 
                if(svClients.clients[i]->authReq == id) {
                    return svClients.clients[i];
                }
            }
            return NULL;
        }

        void authFailed(shared::network::ClientInfo *ci)
        {
            if(!ci) {
                return;
            }
            ci->CleanAuth();
            if(ci->connectAuth) {
                engine::server::Disconnect_Client(ci->clientNumber, ci->connectAuth);
            }
        }

        void AuthFailed(uint id)
        {
            shared::network::ClientInfo *ci = FindAuth(id);
            if (!ci) {
                return;
            }

            ci->CleanAuth();
            if (ci->connectAuth) {
                engine::server::Disconnect_Client(ci->clientNumber, ci->connectAuth);
            }
            //AuthFailed(FindAuth(id));
            //clientinfo *ci = findauth(id);
            //if(!ci) return;
            //ci->cleanauth();
            //if(ci->connectauth) disconnect_client(ci->clientnum, ci->connectauth);
        }

        void AuthSucceeded(uint id)
        {
            shared::network::ClientInfo *ci = FindAuth(id);
            if(!ci) return;
            ci->CleanAuth(ci->connectAuth!=0);
            if(ci->connectAuth) {
                Connected(ci);
            }
            if(ci->authKickVictim >= 0)
            {
                if(SetMaster(ci, true, "", ci->authName, NULL, shared::network::protocol::Priviliges::Auth, false, true))
                    TryKick(ci, ci->authKickVictim, ci->authKickReason, ci->authName, NULL, shared::network::protocol::Priviliges::Auth);
                ci->CleanAuthKick();
            }
            else SetMaster(ci, true, "", ci->authName, NULL, shared::network::protocol::Priviliges::Auth);
        }

        void AuthChallenged(uint id, const char *val, const char *desc = "")
        {
            shared::network::ClientInfo *ci = FindAuth(id);
            if(!ci) return;
            Sendf(ci->clientNumber, 1, "risis", shared::network::protocol::Messages::AuthChallenge, desc, id, val);
        }

        uint nextAuthReq = 0;

        bool TryAuth(shared::network::ClientInfo *ci, const char *user, const char *desc)
        {
            ci->CleanAuth();
            if(!nextAuthReq) nextAuthReq = 1;
            ci->authReq = nextAuthReq++;
            FilterText(ci->authName, user, false, false, 100);
            copycubestr(ci->authDesc, desc);
            if(ci->authDesc[0])
            {
                shared::network::UserKey *u = users.access(UserKey(ci->authName, ci->authDesc));
                if(u)
                {
                    uint seed[3] = { ::hthash(server::serverauth) + detrnd(size_t(ci) + size_t(user) + size_t(desc), 0x10000), uint(shared::network::ftsClient.totalMilliseconds), randomMT() };
                    vector<char> buf;
                    ci->authChallenge = genchallenge(u->pubkey, seed, sizeof(seed), buf);
                    Sendf(ci->clientNumber, 1, "risis", shared::network::protocol::Events::AuthChallenge, desc, ci->authReq, buf.getbuf());
                }
                else ci->CleanAuth();
            }
            else if(!RequestMasterf("reqauth %u %s\n", ci->authReq, ci->authName))
            {
                ci->CleanAuth();
                Sendf(ci->clientNumber, 1, "ris", shared::network::protocol::Messages::ServerMessage, "not connected to authentication server");
            }
            if(ci->authReq) return true;
            if(ci->connectAuth) engine::server::Disconnect_Client(ci->clientNum, ci->connectAuth);
            return false;
        }

        bool AnswerChallenge(shared::network::ServerDynamicEnt *sde, uint id, char *val, const char *desc)
        {
            if (!sde)
                return false;

            // Cast to Ci data.
            ClientInfo *ci = dynamic_cast<ClientInfo>(sde->info);
            if (!ci)
                return false;

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
                if(ci->authChallenge && checkchallange(val, ci->authChallenge))
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
                Sendf(ci->clientNumber, 1, "ris", shared::network::ClientMessage::Disconnect, "not connected to authentication server");
            }
            return ci->authReq || !ci->connectAuth;
        }

    }; // network
}; // game