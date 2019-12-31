#include "cube.h"
#include "ents.h"

#include "game/game.h"
#include "game/server/server.h"
#include "game/client/client.h"

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

#include "game/entities/player.h"

namespace shared {
    namespace network {
         // ServerGame serverGame;
        // Returns true if there already is a client with the same name.
        bool HasClientDuplicateName(entities::classes::BaseClientEntity *ce, const std::string &name)
        {
            std::string nickname = (ce->clientInformation.nickname.empty() ? ce->clientInformation.nickname : "");
            //if(!name) name = ce->nickname;
            loopv(game::clPlayers) {
                if(game::clPlayers[i] != dynamic_cast<entities::classes::Player*>(ce) && ce->clientInformation.nickname != std::string(game::clPlayers[i]->clientInformation.nickname)) {
                    return true;
                }
            }

            return false;
        }

        //
        // ServerDynamicEntInfo, maybe placae into another file?
        //
        ClientInfo::ClientInfo() {
            Reset();
        }
        ClientInfo::~ClientInfo() { 
            events.deletecontents(); 
            CleanClipboard(); 
            CleanAuth(); 
        }

        void ClientInfo::AddEvent(GameEvent *e) {
            // Where CS_SPECTATOR == 5.
            if(state.state == CS_SPECTATOR || events.length()>100) {
            //if(this->state == 5 || events.length()>100)
                delete e;            
            } else {
                events.add(e);
            }
        }

        enum
        {
            PUSHMILLIS = 3000
        };

        extern ENetPeer *GetClientPeer(int i);
        int ClientInfo::CalcPushRange()
        {
            ENetPeer *peer = GetClientPeer(ownerNumber);
            return PUSHMILLIS + (peer ? peer->roundTripTime + peer->roundTripTimeVariance : ENET_PEER_DEFAULT_ROUND_TRIP_TIME);
        }

        bool ClientInfo::CheckPushed(int millis, int range)
        {
            return millis >= timePushed - range && millis <= timePushed + range;
        }

        void ClientInfo::ScheduleExceeded()
        {
            if(state.state!=CS_ALIVE || !serverGame.exceeded) return;
            int range = CalcPushRange();
            if(!serverGame.nextExceeded || serverGame.exceeded + range < serverGame.nextExceeded) serverGame.nextExceeded = serverGame.exceeded + range;
        }

        void ClientInfo::SetExceeded()
        {
            if(state.state==CS_ALIVE && !serverGame.exceeded && !CheckPushed(serverGame.gameMilliseconds, CalcPushRange())) serverGame.exceeded = serverGame.gameMilliseconds;
            ScheduleExceeded();
        }

        void ClientInfo::SetPushed()
        {
            timePushed = max(timePushed, serverGame.gameMilliseconds);
            if(serverGame.exceeded && CheckPushed(serverGame.exceeded, CalcPushRange())) serverGame.exceeded = 0;
        }

        bool ClientInfo::CheckExceeded()
        {
            return state.state == CS_ALIVE && serverGame.exceeded && serverGame.gameMilliseconds > serverGame.exceeded + CalcPushRange();
        }

        void ClientInfo::MapChange()
        {
            mapVote[0] = 0;
            //modeVote = __INT_MAX__;
            state.Reset();
            events.deletecontents();
            overflow = 0;
            timeSync = false;
            timeLastEvent = 0;
            timeExceeded = 0;
            timePushed = 0;
            clientMap[0] = '\0';
            mapCRC = 0;
            warned = false;
            gameClip = false;
        }

        void ClientInfo::Reassign()
        {
            //state.reassign();
            events.deletecontents();
            timeSync = false;
            timeLastEvent = 0;
        }

        void ClientInfo::CleanClipboard(bool fullclean)
        {
            if(clipboard) { 
                if(--clipboard->referenceCount <= 0) 
                    enet_packet_destroy(clipboard); 
                clipboard = NULL; 
            }
            if(fullclean) lastClipboard = 0;
        }

        void ClientInfo::CleanAuthKick()
        {
            authKickVictim = -1;
            DELETEA(authKickReason);
        }

        void ClientInfo::CleanAuth(bool full = true)
        {
            authReq = 0;
            if(authChallenge) {
                freechallenge(authChallenge); 
                authChallenge = NULL; 
            }
            if(full) 
                ServerDynamicEnt::CleanAuthKick();
        }

        void ClientInfo::Reset()
        {
            nickname = "_";
            team = 0;
            //playerModel = -1;
            playerColor = 0;
            privilege = shared::network::protocol::Priviliges::None;
            connected = false;
            local = false;
            connectAuth = 0;
            position.setsize(0);
            messages.setsize(0);
            ping = 0;
            aiReinit = 0;
            needClipboard = 0;
            CleanClipboard();
            CleanAuth();
            MapChange();
        }

        int ServerDynamicEnt::GetEventMilliseconds(int serverMilliseconds, int clientMilliseconds)
        {
            if(!timeSync || (events.empty() && state.WaitExpired(serverMilliseconds)))
            {
                timeSync = true;
                gameOffset = serverMilliseconds - clientMilliseconds;
                return serverMilliseconds;
            }
            else return gameOffset + clientMilliseconds;
        }
            
    }; // network
}; // shared