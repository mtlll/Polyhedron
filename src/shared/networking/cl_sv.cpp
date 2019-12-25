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

namespace shared {
    namespace network {
         // ServerGame serverGame;
        // Returns true if there already is a client with the same name.
        bool HasClientDuplicateName(entities::classes::BaseClientEntity *ce, const std::string &name)
        {
            if(!name) name = ce->name;
            loopv(clients) if(clients[i]!= ci && name != std::string(clients[i]->name))) return true;
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

        void ServerDynamicEntInfo::AddEvent(GameEvent *e)
        {
            if(state == static_cast<uchar>(CS_SPECTATOR) || events.length()>100) delete e;
            else events.add(e);
        }

        enum
        {
            PUSHMILLIS = 3000
        };

        int ClientInfo::CalcPushRange()
        {
            ENetPeer *peer = GetClientPeer(ownerNumber);
            return PUSHMILLIS + (peer ? peer->roundTripTime + peer->roundTripTimeVariance : ENET_PEER_DEFAULT_ROUND_TRIP_TIME);
        }

        bool ClientInfo::CheckPushed(int millis, int range)
        {
            return millis >= pushed - range && millis <= pushed + range;
        }

        void ClientInfo::ScheduleExceeded()
        {
            if(state!=CS_ALIVE || !serverGame.exceeded) return;
            int range = CalcPushRange();
            if(!serverGame.nextExceeded || serverGame.exceeded + range < serverGame.nextExceeded) serverGame.nextExceeded = serverGame.exceeded + range;
        }

        void ClientInfo::SetExceeded()
        {
            if(state==CS_ALIVE && !serverGame.exceeded && !CheckPushed(serverGame.gameMilliseconds, CalcPushRange())) serverGame.exceeded = serverGame.gameMilliseconds;
            ServerDynamicEntInfo::ScheduleExceeded();
        }

        void ClientInfo::SetPushed()
        {
            pushed = max(pushed, serverGame.gameMilliseconds);
            if(serverGame.exceeded && CheckPushed(serverGame.exceeded, CalcPushRange())) serverGame.exceeded = 0;
        }

        bool ServerDynamicEntInfo::CheckExceeded()
        {
            return state == CS_ALIVE && serverGame.exceeded && serverGame.gameMilliseconds > serverGame.exceeded + CalcPushRange();
        }

        void ClientInfo::MapChange()
        {
            mapVote[0] = 0;
            modeVote = INT_MAX;
            state.Reset();
            events.deletecontents();
            overflow = 0;
            timeSync = false;
            lastEvent = 0;
            exceeded = 0;
            pushed = 0;
            clientMap[0] = '\0';
            mapCRC = 0;
            warned = false;
            gameClip = false;
        }

        void ServerDynamicEntInfo::Reassign()
        {
            //state.reassign();
            events.deletecontents();
            timeSync = false;
            lastEvent = 0;
        }

        void ServerDynamicEntInfo::CleanClipboard(bool fullclean = true)
        {
            if(clipboard) { 
                if(--clipboard->referenceCount <= 0) 
                    enet_packet_destroy(clipboard); 
                clipboard = NULL; 
            }
            if(fullclean) lastClipboard = 0;
        }

        void ServerDynamicEntInfo::CleanAuthKick()
        {
            authKickVictim = -1;
            DELETEA(authKickReason);
        }

        void ServerDynamicEntInfo::CleanAuth(bool full = true)
        {
            authReq = 0;
            if(authChallenge) {
                FreeChallenge(authChallenge); 
                authChallenge = NULL; 
            }
            if(full) 
                ServerDynamicEntInfo::CleanAuthKick();
        }

        void ServerDynamicEntInfo::Reset()
        {
            name = "_";
            team = 0;
            playerModel = -1;
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

        int ServerDynamicEntInfo::GetEventMilliseconds(int serverMilliseconds, int clientMilliseconds)
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