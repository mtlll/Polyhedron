#pragma once

namespace game {
    namespace networking {
        namespace protocol {
            
        }

        struct FrameTimeState {
            int currentTime = 0;
            int lastMilliseconds = 1;
            int elapsedTime = 0;
            int totalMilliseconds = 0;
            unsigned int totalSeconds = 0;

            int gameSpeed = 100;
            int paused = 0;
        };
    }
}


extern game::networking::FrameTimeState ftsClient;