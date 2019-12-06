#pragma once

namespace game {
    namespace client {
            // Client Info.

    struct Session {
        int sessionID = 0;
        int mastermode = MM_OPEN;
        int gamespeed = 100;
    };

    struct SessionState {
        bool sendItemsToServer = false; // Mike: This'll change, duh... "after a map change, since server doesn't have map data"
        bool sendCRC = false;           // Mike: This'll change, duh... "after a map change, since server doesn't have map data"
        int lastPing = 0;
        bool demoplayback = false;
        bool gamepaused = false;
    };


            // Connection.
            void gameconnect(bool _remote);
            void gamedisconnect(bool cleanup);

            // Map.
            void changemap(const char *name);
            void forceedit(const char *name);
    } // client
} // game