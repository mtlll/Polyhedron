#pragma once

struct FrameTimeState {
    int currentTime = 0;
    int lastMilliseconds = 1;
    int elapsedTime = 0;
    int totalMilliseconds = 0;
    unsigned int totalSeconds = 0;

    int gamespeed = 100;
    int paused = 0;
};

extern FrameTimeState ftsClient;