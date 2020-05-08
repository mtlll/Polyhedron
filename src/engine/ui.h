#pragma once

namespace UI
{
    bool hascursor();
    void getcursorpos(float &x, float &y);
    void resetcursor();
    bool movecursor(int dx, int dy);
    bool keypress(int code, bool isdown);
    bool textinput(const char *str, int len);
    float abovehud();

    void setup();
    void update();
    void render();
    void cleanup();
}