#pragma once

namespace shared {
    namespace network {
        //
        // Main client frame state(s) and timers, encapsulated neatly in a struct.
        // it is officially defined in main.cpp (Where our main loop resides, for now).
        // Why is it in this namespace then? Simple, the game runs by networking, so we
        // might as well consider it the CURRENT Frame its Time & State.
        //

        // Should be a struct, server frame time state.
		struct ServerFrameTimeState {
			int gameMode = 0;
			int gameMilliseconds = 0;
			int gameLimit = 0;
			int nextExceeded = 0;
			int gameSpeed = 100;

			bool gamePaused = false;
			bool shouldstep = true;
			bool notgotitems = true;        // true when map has changed and waiting for clients to send item

			int intermission = 0;
			enet_uint32 lastSend = 0;

			std::string serverMapName = "";
			stream *mapData = NULL;

		}; extern ServerFrameTimeState ftsServer;  
    }; // network
}; // shared
