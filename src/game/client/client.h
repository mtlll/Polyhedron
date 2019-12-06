#pragma once

namespace game {
    namespace client {
        // Client Info.

        struct Session {
            int sessionID = 0;
            int masterMode = MM_OPEN;
            int gameSpeed = 100;
        };

        struct SessionState {
            bool sendItemsToServer = false; // Mike: This'll change, duh... "after a map change, since server doesn't have map data"
            bool sendCRC = false;           // Mike: This'll change, duh... "after a map change, since server doesn't have map data"

            bool demoPlayBack = false;
            bool gamePaused = false;

            int lastPing = 0;
        };


        // Connection.
        void GameConnect(bool _remote);
        void GameDisconnect(bool cleanup);

        // Map.
        void ChangeMap(const char *name);
        void ForceEdit(const char *name);
    } // client
} // game