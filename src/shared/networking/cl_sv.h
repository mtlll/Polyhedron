#pragma once

#include "game/server/server.h"
#include "game/client/client.h"

namespace game {
    // network messages codes, c2s, c2c, s2c
    namespace networking {
        namespace protocol {
            enum struct Priviliges : int;
            enum struct Events : int;
            enum struct MasterMode : int;
        };

        //
        // Our implementation of ClientInfo.
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
            game::networking::protocol::Priviliges privilege;
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
      
        // Returns a coloured string of a name.
        const char *GenerateClientColorName(game::networking::ClientInfo *ci, const std::string &name = "unnamed");
    };
};