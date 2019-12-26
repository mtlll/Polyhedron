#pragma once

#include "../cube.h"
#include "../ents.h"

#include "game/game.h"

#include "shared/networking/network.h"
#include "shared/networking/protocol.h"
#include "shared/networking/frametimestate.h"

namespace shared {
    // Networking
    namespace network {
        // Protocol predefinitions.
        namespace protocol {
            enum struct Messages : enet_uint32;
            enum struct NetClientMessage : enet_uint32;
            enum struct ConsoleMessage : enet_uint32;            
            enum struct DisconnectReason : enet_uint32;

            //
            // A class enum copy of the old default priviliges
            //
            enum struct Priviliges : int { 
                None = 0, Master, Auth, Admin
            };

            //
            // Master Mode Masks.
            //
            enum struct MasterMask : int {
                Auth = -1, OpenServer, Cooperative, Veto, Locked, PrivateServer, Password, Start = Auth
            };
        };
        
        //
        // ServerState, empty, local, or TcpIP.
        //
        enum class ServerState : int {
            Empty = 0, Local,TcpIP 
        };

        //
        // Our implementation of the "Dynent" type in old Tesseract, now named. ServerDynamicEnt structure.
        //
        struct ServerDynamicEnt {                   // server side version of "dynent" type       {
        public:
            int clientNumber;
            cubestr hostName;
            ENetPeer *peer;
            shared::network::ServerState type;
            void *info;
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
            int gameMilliseconds = 0;
            int gameLimit = 0;
            int exceeded = 0;
            int nextExceeded = 0;
            int gameSpeed = 100;
            bool gamePaused = false;
            bool shouldStep = true;

            shared::network::protocol::GameMode gameMode = shared::network::protocol::GameMode::Local;

            cubestr serverMapName = "";
            int intermission = 0;
            enet_uint32 lastSend = 0;
            shared::network::protocol::MasterMode masterMode = shared::network::protocol::MasterMode::Open;
            shared::network::protocol::MasterMask masterMask = shared::network::protocol::MasterMask::PrivateServer;
            stream *mapData = NULL;

            vector<uint> allowedIPs;
            vector<ban> bannedIPs;
        }; extern ServerGame serverGame;

        // Client Session Info.
        // struct ClientServerSession
        // {
        //     int sessionID = 0;
        //     int gameSpeed = 100;
        //     ::game::networking::protocol::MasterMode masterMode;
        // };

        // Client Session State info.
        // struct ClientServerSessionState
        // {
        //     bool sendItemsToServer = false; // Mike: This'll change, duh... "after a map change, since server doesn't have map data"
        //     bool sendCRC = false;           // Mike: This'll change, duh... "after a map change, since server doesn't have map data"

        //     bool demoPlayBack = false;
        //     bool gamePaused = false;

        //     int lastPing = 0;
        // };

        class GameEvent {
        //    void WTF();
        };

        //
        // Server side client info.
        //
        //
        // Client Info.
        //
        class ClientInfo {
        public:
            ClientInfo();
            ~ClientInfo();

            // Client and Owner number.
            int clientNumber = 0;           // Client number.
            int ownerNumber = 0;            // TODO: WatIsDeze: Owner client number. (Seems to be used for bot AI, which are.. clients running in your client. Super army cheat hacks, I bet someone did those.. bad old code)
            int connectedMilliseconds = 0;  // Connection MS duration.

            int sessionID = 0;              // ENET Peer Session ID.
            int overflow = 0;               // Overflow??
            int team = 0;                   // Team number. WatIsDeze: TODO: We need this still?

            int playerModelID = 0;          // Player Model ID.
            int playerColor = 0;            // Player Model Color.

            // Client personal relations.
            std::string nickname = "unnamed_ci";
            shared::network::protocol::Priviliges privilege = shared::network::protocol::Priviliges::None;
            bool connected = false;
            bool local = false;
            bool timeSync = false;
            
            // Time related.
            int gameOffset = 0;
            int lastEvent = 0;
            int pushed = 0;
            int exceeded = 0;
            int state = 0;

            vector<GameEvent *> events; // GameEvents vector for this ClientInfo
            vector<uchar> position;     // TODO: unsigned char position?
            vector<uchar> messages;     // TODO: What does it? List of unsigned char messages.
            
            uchar *wsdata;              // WorldState data.
            int wslen;                  // WorldState data length.
            
            vector<ClientInfo *> bots;  // The bots/ai that this client controls. I know, it's odd, the server should do this imo.
            
            int ping = 0;               // The ping of this client.
            int aiReinit = 0;           // Reinitialize AI??

            cubestr clientMap;          // Speaks for itself.
            cubestr mapVote;            // Suppose the voted for mapname.

            int mapCRC = 0;             // The CRC of the map.

            bool warned = false;        // Client has been warned
            bool gameClip = false;      // I suppose this means, noclip.
            
            int lastClipboard = 0;      // No fucking idea.
            int needClipboard = 0;      // No fucking idea.
            
            ENetPacket *getDemo;        // An ENetPacket for receiving a demo.
            ENetPacket *getMap;         // An ENetPacket for receiving a map.
            ENetPacket *clipboard;      // An ENetPacket for receiving these "I have no fucking idea" things with.

            cubestr authName;
            cubestr authDesc;
            
            uint authReq = 0;           // Authentication required?
            int connectAuth = 0;        // Connected to Auth?
            
            int authKickVictim = 0;     // Suppose the ID of the victim that gets kicked due to bad Authorization.
            char *authKickReason;       // A reasoning why.
            void *authChallenge;        // No fucking idea.

            void AddEvent(GameEvent *e);

            enum
            {
                PUSHMILLIS = 3000
            };

            int CalcPushRange();

            bool CheckPushed(int millis, int range);

            void ScheduleExceeded();

            void SetExceeded();

            void SetPushed();

            bool CheckExceeded();

            void MapChange();

            void Reassign();

            void CleanClipboard(bool fullclean = true);

            void CleanAuthKick();

            void CleanAuth(bool full = true);

            void Reset();

            int GetEventMilliseconds(int serverMilliseconds, int clientMilliseconds);
        };

        // // Returns a coloured string of a name.
        
    }; // server
}; // game
