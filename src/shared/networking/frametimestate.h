#pragma once

namespace shared {
    namespace network {
        //
        // Main client frame state(s) and timers, encapsulated neatly in a struct.
        // it is officially defined in main.cpp (Where our main loop resides, for now).
        // Why is it in this namespace then? Simple, the game runs by networking, so we
        // might as well consider it the CURRENT Frame its Time & State.
        //
        struct FrameTimeState {
            // Originially from main.cpp (Fetch old source of Tesseract in case this is still confusing you.)
            int currentTime = 0;                // The current frequency time captured from SDL this frame.
            int lastMilliseconds = 1;           // Last Milliseconds, ya gotta have 'em
            int elapsedTime = 0;                // The elapsed time. (Per frame? Suppose so.)
            int totalMilliseconds = 1;          // Total amount of Milliseconds that have passed.
            unsigned int totalSeconds = 0;      // Total seconds which have passed.

            // These are here, because they are part of a client frame time state. Less (external)globals does us well!
            int gameSpeed = 100;
            int paused = 0;
        };
        extern FrameTimeState ftsClient;
    };
};