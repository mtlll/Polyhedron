#pragma once

#include "game/game.h"
#include "game/server/server.h"

#include "shared/networking/network.h"
#include "shared/networking/cl_sv.h"
#include "shared/networking/protocol.h"
#include "shared/networking/frametimestate.h"

namespace game
{
    namespace networking {
        namespace protocol {
            //
            // Enum class copy MasterMode flags. Open to join, password, vote, locked etc.
            //
            enum struct MasterMode : int;
        };
    };
    namespace client
    {
        // Client Session Info.
        struct Session
        {
            int sessionID = 0;
            int gameSpeed = 100;
            ::game::networking::protocol::MasterMode masterMode;
        };

        // Client Session State info.
        struct SessionState
        {
            bool sendItemsToServer = false; // Mike: This'll change, duh... "after a map change, since server doesn't have map data"
            bool sendCRC = false;           // Mike: This'll change, duh... "after a map change, since server doesn't have map data"

            bool demoPlayBack = false;
            bool gamePaused = false;

            int lastPing = 0;
        };

        // Connection.
        extern void GameConnect(bool _remote);
        extern void GameDisconnect(bool cleanup);

        // Messaging.
        extern bool AddMessage(::networking::protocol::NetClientMessage type, const char *fmt, ...);

        // Map.
        extern void ChangeMap(const char *name);
        extern void ForceEdit(const char *name);
    } // namespace client
} // namespace game