#pragma once

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

namespace game {
    namespace networking {
        // Protocol predefinitions.
        namespace protocol {
            enum struct Priviliges : int;
            enum struct Events : int;
            enum struct MasterMode : int;

            //
            // Master Mode Masks.
            //
            enum struct MasterMask : int {
                Mode = 0xF,
                AutoApprove = 0x1000,
                PrivateServer = (Mode | AutoApprove),
                PublicServer = ((1 << static_cast<int>(protocol::MasterMode::Open)) | (1 << static_cast<int>(protocol::MasterMode::Veto))),
                CoopServer = (AutoApprove | PublicServer | (1 << static_cast<int>(protocol::MasterMode::Locked)))
            };
        };
        
        //
        // ServerState, empty, local, or TcpIP.
        //
        enum class ServerState {
            Empty = 0,
            Local,
            TcpIP 
        };

        //
        // Our implementation of the ServerClient structure.
        //
        struct ServerClient {                   // server side version of "dynent" type       {
        public:
            int clientNumber;
            cubestr hostName;
            ENetPeer *peer;

            game::networking::ServerState type;
            void *info;
        };

        //
        // Client Info.
        //
        struct ClientInfo {
        public:
            // Client and Owner number.
            int clientNumber = 0;           // Client number.
            int ownerNumber = 0;            // Owner client number.
            int connectMilliseconds = 0;    // Connection MS duration.

            int sessionID = 0;              // ENET Peer Session ID.
            int overflow = 0;               // Overflow??

            int playerModelID = 0;            // PLayer Model ID.
            int lifeSequence = 0;             // LifeSequence?

            // Client personal relations.
            cubestr name;
            protocol::Priviliges privilege;
            bool local = false;
            bool connected = false;
            
            // Time related.
            bool timeSync = false;
            int gameOffset = 0;
            int lastEvent = 0;
            int pushed = 0;
            int exceeded = 0;

            // Temporarily?
            int team = 0;
        };
        

        //
        // Idk where this came from.
        //
        struct ban
        {
            int time, expire;
            uint ip;
        };

        //
        // ServerGame state.
        //
        struct ServerGame {
            bool notGotItems = true;        // true when map has changed and waiting for clients to send item
            GameMode gameMode = GameMode::Local;
            int gameMilliseconds = 0;
            int gameLimit = 0;
            int exceeded = 0;
            int nextExceeded = 0;
            int gameSpeed = 100;
            bool gamePaused = false;
            bool shouldStep = true;

            cubestr serverMapName = "";
            int intermission = 0;
            enet_uint32 lastSend = 0;
            protocol::MasterMode masterMode = protocol::MasterMode::Open;
            protocol::MasterMask masterMask = protocol::MasterMask::PrivateServer;
            stream *mapData = NULL;

            vector<uint> allowedIPs;
            vector<ban> bannedIPs;
        };

        // ServerGame
        extern ServerGame serverGame;

        // Client Session Info.
        struct ClientServerSession
        {
            int sessionID = 0;
            int gameSpeed = 100;
            ::game::networking::protocol::MasterMode masterMode;
        };

        // Client Session State info.
        struct ClientServerSessionState
        {
            bool sendItemsToServer = false; // Mike: This'll change, duh... "after a map change, since server doesn't have map data"
            bool sendCRC = false;           // Mike: This'll change, duh... "after a map change, since server doesn't have map data"

            bool demoPlayBack = false;
            bool gamePaused = false;

            int lastPing = 0;
        };

        class GameEvent {
            void WTF();
        };

        //
        // Server side client info.
        //
        struct ServerClientInfo
        {
            int clientNumber = 0;
            int ownerNumber = 0;
            int connectedMilliseconds = 0;
            int sessionID = 0;
            int overflow;
            cubestr name;
            cubestr mapVote;
            int team = 0;
            int playerModel = 0; 
            int playerColor = 0;
            int modeVote = 0;
            protocol::Priviliges privilege = protocol::Priviliges::None;
            bool connected = false;
            bool local = false;
            bool timeSync = false;
            int gameOffset = 0;
            int lastEvent = 0;
            int pushed = 0; 
            int exceeded = 0;
            int state;
            vector<GameEvent *> events;
            vector<uchar> position, messages;
            uchar *wsdata;
            int wslen;
            vector<ClientInfo *> bots;
            int ping, aiReinit;
            cubestr clientMap;
            int mapCRC;
            bool warned, gameClip;
            ENetPacket *getDemo;
            ENetPacket *getMap;
            ENetPacket *clipboard;
            int lastClipboard = 0;
            int needClipboard = 0;
            int connectAuth = 0;
            uint authReq = 0;
            cubestr authName;
            cubestr authDesc;
            void *authChallenge;
            int authKickVictim = 0;
            char *authKickReason;

            ServerClientInfo() {
                Reset();
            }
            ~ServerClientInfo() { 
                events.deletecontents(); 
                CleanClipboard(); 
                CleanAuth(); 
            }

            void AddEvent(GameEvent *e)
            {
                if(state ==static_cast<uchar>(CS_SPECTATOR) || events.length()>100) delete e;
                else events.add(e);
            }

            enum
            {
                PUSHMILLIS = 3000
            };

            int CalcPushRange()
            {
                ENetPeer *peer = GetClientPeer(ownerNumber);
                return PUSHMILLIS + (peer ? peer->roundTripTime + peer->roundTripTimeVariance : ENET_PEER_DEFAULT_ROUND_TRIP_TIME);
            }

            bool CheckPushed(int millis, int range)
            {
                return millis >= pushed - range && millis <= pushed + range;
            }

            void ScheduleExceeded()
            {
                if(state!=CS_ALIVE || !gameServer.exceeded) return;
                int range = CalcPushRange();
                if(!serverGame.nextExceeded || serverGame.exceeded + range < serverGame.nextExceeded) serverGame.nextExceeded = serverGame.exceeded + range;
            }

            void SetExceeded()
            {
                if(state==CS_ALIVE && !serverGame.exceeded && !CheckPushed(serverGame.gameMilliseconds, CalcPushRange())) exceeded = gameMilliseconds;
                ScheduleExceeded();
            }

            void SetPushed()
            {
                pushed = max(pushed, serverGame.gameMilliseconds);
                if(exceeded && CheckPushed(serverGame.exceeded, CalcPushRange())) serverGame.exceeded = 0;
            }

            bool CheckExceeded()
            {
                return state == CS_ALIVE && serverGame.exceeded && serverGame.gameMilliseconds > serverGame.exceeded + CalcPushRange();
            }

            void MapChange()
            {
                mapVote[0] = 0;
                modeVote = INT_MAX;
                //state.Reset();
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

            void Reassign()
            {
                //state.reassign();
                events.deletecontents();
                timeSync = false;
                lastEvent = 0;
            }

            void CleanClipboard(bool fullclean = true)
            {
                if(clipboard) { if(--clipboard->referenceCount <= 0) enet_packet_destroy(clipboard); clipboard = NULL; }
                if(fullclean) lastClipboard = 0;
            }

            void CleanAuthKick()
            {
                authKickVictim = -1;
                DELETEA(authKickReason);
            }

            void CleanAuth(bool full = true)
            {
                authReq = 0;
                if(authChallenge) {
                    FreeChallenge(authChallenge); 
                    authChallenge = NULL; 
                }
                if(full) 
                    CleanAuthKick();
            }

            void Reset()
            {
                name = "_";
                team = 0;
                playerModel = -1;
                playerColor = 0;
                privilege = protocol::Priviliges::None;
                connected = local = false;
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

            int GetEventMilliseconds(int serverMilliseconds, int clientMilliseconds)
            {
                if(!timeSync || (events.empty() && state.WaitExpired(serverMilliseconds)))
                {
                    timeSync = true;
                    gameOffset = serverMilliseconds - clientMilliseconds;
                    return serverMilliseconds;
                }
                else return gameOffset + clientMilliseconds;
            }
        };

        // Returns a coloured string of a name.
        const char *GenerateClientColorName(game::networking::ClientInfo *ci, const std::string &name = "unnamed");
    }; // server
}; // game
