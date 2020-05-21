#pragma once
#include <SDL_events.h>

class Application;

class Input
{
public:
    Input(Application& app);
    ~Input();

    void HandleEvent(const SDL_Event& event);

    void Grab(bool enable = true);

    void Text(bool enable = true);

    bool InterceptKey(SDL_KeyCode key);
private:
    bool m_IsTyping;
    Application& m_App;
};


