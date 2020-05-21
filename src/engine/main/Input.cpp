#include "Input.h"
#include "Application.h"
#include "engine/console.h"
#include "shared/types.h"
#include "engine/physics.h"
#include "engine/ui.h"
#include <SDL_events.h>

//FIXME: extern
extern size_t decodeutf8(uchar *dst, size_t dstlen, const uchar *src, size_t srclen, size_t *carry);

Input::Input(Application& app)
    : m_App(app)
{
}

Input::~Input()
{
    SDL_ShowCursor(SDL_TRUE);
    SDL_SetRelativeMouseMode(SDL_FALSE);
//    if(screen) SDL_SetWindowGrab(screen, SDL_FALSE);
}

void Input::HandleEvent(const SDL_Event& event)
{
    switch(event.type)
    {
        case SDL_TEXTINPUT:
            if (m_IsTyping)
            {
                uchar buf[SDL_TEXTINPUTEVENT_TEXT_SIZE+1];
                size_t len = decodeutf8(buf, sizeof(buf)-1, (const uchar *)event.text.text, strlen(event.text.text));
                if(len > 0)
                {
                    buf[len] = '\0';
                    processtextinput((const char *)buf, len);
                }
            }
            break;

        case SDL_KEYDOWN:
        case SDL_KEYUP:
            if (!event.key.repeat)
            {
                processkey(event.key.keysym.sym, event.key.state == SDL_PRESSED);
            }
            break;


        case SDL_MOUSEMOTION:
            {
                int dx = event.motion.xrel, dy = event.motion.yrel;
                if(!UI::movecursor(dx, dy))
                {
                    mousemove(dx, dy);
                }
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP:
            switch(event.button.button)
            {
                case SDL_BUTTON_LEFT: processkey(-1, event.button.state==SDL_PRESSED); break;
                case SDL_BUTTON_MIDDLE: processkey(-2, event.button.state==SDL_PRESSED); break;
                case SDL_BUTTON_RIGHT: processkey(-3, event.button.state==SDL_PRESSED); break;
                case SDL_BUTTON_X1: processkey(-6, event.button.state==SDL_PRESSED); break;
                case SDL_BUTTON_X2: processkey(-7, event.button.state==SDL_PRESSED); break;
            }
            break;

        case SDL_MOUSEWHEEL: {
            if(event.wheel.y > 0)
            {
                processkey(-4, true);
                processkey(-4, false);
            }
            else if(event.wheel.y < 0)
            {
                processkey(-5, true);
                processkey(-5, false);
            }
        } break;
    }
}

void Input::Grab(bool enable)
{
    if(enable)
    {
//#ifndef NDEBUG
//		SDL_ShowCursor(SDL_FALSE); // WatIsDeze: Set to true to hide system cursor. (Otherwise debugging is a bitch on Linux)
//#else
//		SDL_ShowCursor(SDL_TRUE); // WatIsDeze: Set to true to hide system cursor. (Otherwise debugging is a bitch on Linux)
//#endif
//		if(canrelativemouse && userelativemouse)
//		{
//			if(SDL_SetRelativeMouseMode(SDL_TRUE) >= 0)
//			{
//				SDL_SetWindowGrab(screen, SDL_TRUE);
//				relativemouse = true;
//			}
//			else
//			{
//				SDL_SetWindowGrab(screen, SDL_FALSE);
//				canrelativemouse = false;
//				relativemouse = false;
//			}
//		}
    }
    else
    {
//#ifndef NDEBUG
//		SDL_ShowCursor(SDL_FALSE); // WatIsDeze: Set to true to hide system cursor. (Otherwise debugging is a bitch on Linux)
//#else
//		SDL_ShowCursor(SDL_TRUE); // WatIsDeze: Set to true to hide system cursor. (Otherwise debugging is a bitch on Linux)
//#endif
//		if(relativemouse)
//		{
//			SDL_SetRelativeMouseMode(SDL_FALSE);
//			SDL_SetWindowGrab(screen, SDL_FALSE);
//			relativemouse = false;
//		}
    }
}

void Input::Text(bool enable)
{
    if (enable)
    {
        SDL_StartTextInput();
    }
    else
    {
        SDL_StopTextInput();
    }

    m_IsTyping = enable;
}

bool Input::InterceptKey(SDL_KeyCode key)
{
    bool intercepted = false;
    m_App.PeekEvents([&](SDL_Event& event) -> Application::PeekEventAction {
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == key)
            {
                intercepted = true;
                return Application::PeekEventAction::Drop;
            }
        }

        return Application::PeekEventAction::Cache;
    });

    return intercepted;
}
