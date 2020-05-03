#include "nuklear_polyhedron.h"
#include "shared/cube.h"
#include "engine/engine.h"
#define NK_IMPLEMENTATION
#include "nuklear.h"
#include "glemu.h"
#include "tools.h"
#include "texture.h"
#include "engine/font.h"

NkPolyhedron::NkFont::NkFont(std::string fontName) {
    m_FontName = "default";
    m_UserFont.userdata = nk_handle_ptr(this);
    font* fontInstance = findfont(m_FontName.c_str());
    auto fontScale = 1.0f;//float(fontInstance->c);
    m_UserFont.height = 32.0f;//fontInstance->scale;
    m_UserFont.width = &UserFontGetWidth;
}

float NkPolyhedron::UserFontGetWidth(nk_handle fontInstance, float h, const char* text, int len)
{
    NkFont *font = (NkFont*)fontInstance.ptr;
    if (!font || !text || len == 0)
    {
        return 0.0f;
    }

    auto fontObject = findfont(font->m_FontName.c_str());
    auto fontScale = float(fontObject->scale);
    float scale = h / fontScale;

    auto fontLen = text_widthf(std::string(text, len).c_str());

    return fontLen * scale;
}

NkPolyhedron::NkPolyhedron()
    : m_DefaultFont(std::make_unique<NkFont>("default_outline"))
{
    //m_Shader = lookupshaderbyname("hud");
    nk_buffer_init_default(&m_NkBuffer);
    nk_init_default(&m_Context, &m_DefaultFont->m_UserFont);
}

void NkPolyhedron::Render()
{
    const nk_command* cmd;
    nk_foreach(cmd, &m_Context)
    {
        switch (cmd->type) {
            case NK_COMMAND_NOP: break;
            case NK_COMMAND_SCISSOR: {
                const auto* scissorCmd = reinterpret_cast<const nk_command_scissor*>(cmd);
                glCheckError(glScissor(scissorCmd->x, scissorCmd->y, scissorCmd->w, scissorCmd->h));
            } break;
            case NK_COMMAND_LINE: {
                const auto* lineCmd = reinterpret_cast<const nk_command_line*>(cmd);

                gle::defvertex(2);
                gle::defcolor(4, GL_UNSIGNED_BYTE);
                glCheckError(glLineWidth(lineCmd->line_thickness));

                gle::begin(GL_LINE_LOOP);
                gle::attribf(float(lineCmd->begin.x), float(lineCmd->begin.y));
                gle::attribub(lineCmd->color.r, lineCmd->color.g, lineCmd->color.b, lineCmd->color.a);

                gle::attribf(float(lineCmd->end.x), float(lineCmd->end.y));
                gle::attribub(lineCmd->color.r, lineCmd->color.g, lineCmd->color.b, lineCmd->color.a);

                xtraverts += gle::end();
            } break;
            case NK_COMMAND_RECT: {
                const auto* rectCmd = reinterpret_cast<const nk_command_rect*>(cmd);

                gle::defvertex(2);
                gle::defcolor(4, GL_UNSIGNED_BYTE);

                gle::begin(GL_LINE_LOOP);

                gle::attribf(rectCmd->x             , rectCmd->y);
                gle::attribub(rectCmd->color.r, rectCmd->color.g, rectCmd->color.b, rectCmd->color.a);

                gle::attribf(rectCmd->x + rectCmd->w, rectCmd->y);
                gle::attribub(rectCmd->color.r, rectCmd->color.g, rectCmd->color.b, rectCmd->color.a);

                gle::attribf(rectCmd->x + rectCmd->w, rectCmd->y + rectCmd->h);
                gle::attribub(rectCmd->color.r, rectCmd->color.g, rectCmd->color.b, rectCmd->color.a);

                gle::attribf(rectCmd->x             , rectCmd->y + rectCmd->h);
                gle::attribub(rectCmd->color.r, rectCmd->color.g, rectCmd->color.b, rectCmd->color.a);

                xtraverts += gle::end();
            } break;
            case NK_COMMAND_RECT_FILLED: {
                const auto* rectCmd = reinterpret_cast<const nk_command_rect_filled*>(cmd);

                gle::defvertex(2);
                gle::defcolor(4, GL_UNSIGNED_BYTE);

                gle::begin(GL_TRIANGLE_STRIP);

                gle::attribf(rectCmd->x + rectCmd->w, rectCmd->y);
                gle::attribub(rectCmd->color.r, rectCmd->color.g, rectCmd->color.b, rectCmd->color.a);

                gle::attribf(rectCmd->x             , rectCmd->y);
                gle::attribub(rectCmd->color.r, rectCmd->color.g, rectCmd->color.b, rectCmd->color.a);

                gle::attribf(rectCmd->x + rectCmd->w, rectCmd->y + rectCmd->h);
                gle::attribub(rectCmd->color.r, rectCmd->color.g, rectCmd->color.b, rectCmd->color.a);

                gle::attribf(rectCmd->x             , rectCmd->y + rectCmd->h);
                gle::attribub(rectCmd->color.r, rectCmd->color.g, rectCmd->color.b, rectCmd->color.a);

                xtraverts += gle::end();
            } break;
            case NK_COMMAND_CIRCLE: {
                const auto* circleCmd = reinterpret_cast<const nk_command_circle*>(cmd);
                vec2 ptr (1.0f, 0.0f);
                float w = circleCmd->w;
                float h = circleCmd->h;
                float rw = w / 2.0f;
                float rh = h / 2.0f;
                float x = float(circleCmd->x) + rw;
                float y = float(circleCmd->y) + rh;

                float circum = sqrt(rw * rw + rh * rh) * PI * 2.0f;
                int segmentCount = std::max(8, int(circum / 15.0f));
                float anglePerSegment = (PI * 2) / float(segmentCount);

                gle::defvertex(2);
                gle::defcolor(4, GL_UNSIGNED_BYTE);
                glCheckError(glLineWidth(circleCmd->line_thickness));

                gle::begin(GL_LINE_LOOP);

                for (int i = 0; i < segmentCount; ++i)
                {
                    gle::attribf(x + ptr.x * rw, y + ptr.y * rh);
                    gle::attribub(circleCmd->color.r, circleCmd->color.g, circleCmd->color.b, circleCmd->color.a);

                    ptr.rotate_around_z(anglePerSegment);
                }

                xtraverts += gle::end();
            } break;
            case NK_COMMAND_CIRCLE_FILLED: {
                const auto* circleCmd = reinterpret_cast<const nk_command_circle_filled*>(cmd);
                vec2 ptr (1.0f, 0.0f);
                float w = circleCmd->w;
                float h = circleCmd->h;
                float rw = w / 2.0f;
                float rh = h / 2.0f;
                float x = float(circleCmd->x) + rw;
                float y = float(circleCmd->y) + rh;

                float circum = sqrt(rw * rw + rh * rh) * PI * 2.0f;
                int segmentCount = std::max(8, int(circum / 15.0f));
                float anglePerSegment = (PI * 2) / float(segmentCount);

                gle::defvertex(2);
                gle::defcolor(4, GL_UNSIGNED_BYTE);

                gle::begin(GL_TRIANGLE_FAN);

                gle::attribf(x, y);
                gle::attribub(circleCmd->color.r, circleCmd->color.g, circleCmd->color.b, circleCmd->color.a);

                gle::attribf(x + ptr.x * rw, y + ptr.y * rh);
                gle::attribub(circleCmd->color.r, circleCmd->color.g, circleCmd->color.b, circleCmd->color.a);

                for (int i = 0; i < segmentCount; ++i)
                {
                    ptr.rotate_around_z(anglePerSegment);

                    gle::attribf(x + ptr.x * rw, y + ptr.y * rh);
                    gle::attribub(circleCmd->color.r, circleCmd->color.g, circleCmd->color.b, circleCmd->color.a);
                }

                xtraverts += gle::end();
            } break;
            case NK_COMMAND_TRIANGLE: {

            } break;
            case NK_COMMAND_TRIANGLE_FILLED: {

            } break;
            case NK_COMMAND_POLYGON: {

            } break;
            case NK_COMMAND_POLYGON_FILLED: {

            } break;
            case NK_COMMAND_POLYLINE: {

            } break;
            case NK_COMMAND_TEXT: {
                const auto* textCmd = reinterpret_cast<const nk_command_text*>(cmd);
                float x = textCmd->x;
                float y = textCmd->y;
                float w = textCmd->w;
                float h = textCmd->h;

                std::string str(textCmd->string, textCmd->length);
                pushfont();
                auto textFont = reinterpret_cast<NkFont*>(textCmd->font->userdata.ptr);
                auto fontObject = findfont(textFont->m_FontName.c_str());
                auto fontScale = float(fontObject->scale);
                setfont(fontObject);
                float oldscale = textscale;
//                textscale = h / float(fontObject->defaulth);
                textscale = float(textCmd->font->height) / fontScale;
                float textscaleInv = 1.0f / textscale;
                glCheckError(glEnable(GL_BLEND));
                draw_text(
                    str.c_str(),
                    x * textscaleInv, y * textscaleInv,
                    textCmd->foreground.r,
                    textCmd->foreground.g,
                    textCmd->foreground.b,
                    textCmd->foreground.a
                );
                glCheckError(glDisable(GL_BLEND));
                textscale = oldscale;
                popfont();
            } break;
            case NK_COMMAND_CURVE: {

            } break;
            case NK_COMMAND_ARC: {

            } break;
            case NK_COMMAND_RECT_MULTI_COLOR: {

            } break;
            case NK_COMMAND_IMAGE: {
                const auto* imageCmd = reinterpret_cast<const nk_command_image*>(cmd);

                gle::defvertex(2);
                gle::defcolor(4, GL_UNSIGNED_BYTE);
                gle::deftexcoord0();

                gle::begin(GL_TRIANGLE_STRIP);

                gle::attribf(imageCmd->x + imageCmd->w, imageCmd->y);
                gle::attribub(imageCmd->col.r, imageCmd->col.g, imageCmd->col.b, imageCmd->col.a);
                gle::attribf(imageCmd->img.region[0], imageCmd->img.region[0]);

                gle::attribf(imageCmd->x             , imageCmd->y);
                gle::attribub(imageCmd->col.r, imageCmd->col.g, imageCmd->col.b, imageCmd->col.a);
                gle::attribf(imageCmd->img.region[0], imageCmd->img.region[1]);

                gle::attribf(imageCmd->x + imageCmd->w, imageCmd->y + imageCmd->h);
                gle::attribub(imageCmd->col.r, imageCmd->col.g, imageCmd->col.b, imageCmd->col.a);
                gle::attribf(imageCmd->img.region[1], imageCmd->img.region[1]);

                gle::attribf(imageCmd->x             , imageCmd->y + imageCmd->h);
                gle::attribub(imageCmd->col.r, imageCmd->col.g, imageCmd->col.b, imageCmd->col.a);
                gle::attribf(imageCmd->img.region[1], imageCmd->img.region[0]);

                xtraverts += gle::end();
            } break;
            case NK_COMMAND_ARC_FILLED: {

            } break;
            default: break;
        }
    }

    nk_clear(&m_Context);
}

void NkPolyhedron::InputProcessBegin()
{
    nk_input_begin(&m_Context);
}

void NkPolyhedron::InputProcessEnd()
{
    nk_input_end(&m_Context);
}

NkPolyhedron::InputEventProcessState NkPolyhedron::InputEvent(const SDL_Event &evt)
{
    if (evt.type == SDL_KEYUP || evt.type == SDL_KEYDOWN)
    {
        /* key events */
        int down = evt.type == SDL_KEYDOWN;
        const Uint8* state = SDL_GetKeyboardState(0);
        SDL_Keycode sym = evt.key.keysym.sym;
        if (sym == SDLK_RSHIFT || sym == SDLK_LSHIFT)
            nk_input_key(&m_Context, NK_KEY_SHIFT, down);
        else if (sym == SDLK_DELETE)
            nk_input_key(&m_Context, NK_KEY_DEL, down);
        else if (sym == SDLK_RETURN)
            nk_input_key(&m_Context, NK_KEY_ENTER, down);
        else if (sym == SDLK_TAB)
            nk_input_key(&m_Context, NK_KEY_TAB, down);
        else if (sym == SDLK_BACKSPACE)
            nk_input_key(&m_Context, NK_KEY_BACKSPACE, down);
        else if (sym == SDLK_HOME)
        {
            nk_input_key(&m_Context, NK_KEY_TEXT_START, down);
            nk_input_key(&m_Context, NK_KEY_SCROLL_START, down);
        }
        else if (sym == SDLK_END)
        {
            nk_input_key(&m_Context, NK_KEY_TEXT_END, down);
            nk_input_key(&m_Context, NK_KEY_SCROLL_END, down);
        }
        else if (sym == SDLK_PAGEDOWN)
        {
            nk_input_key(&m_Context, NK_KEY_SCROLL_DOWN, down);
        }
        else if (sym == SDLK_PAGEUP)
        {
            nk_input_key(&m_Context, NK_KEY_SCROLL_UP, down);
        }
        else if (sym == SDLK_z)
            nk_input_key(&m_Context, NK_KEY_TEXT_UNDO, down && state[SDL_SCANCODE_LCTRL]);
        else if (sym == SDLK_r)
            nk_input_key(&m_Context, NK_KEY_TEXT_REDO, down && state[SDL_SCANCODE_LCTRL]);
        else if (sym == SDLK_c)
            nk_input_key(&m_Context, NK_KEY_COPY, down && state[SDL_SCANCODE_LCTRL]);
        else if (sym == SDLK_v)
            nk_input_key(&m_Context, NK_KEY_PASTE, down && state[SDL_SCANCODE_LCTRL]);
        else if (sym == SDLK_x)
            nk_input_key(&m_Context, NK_KEY_CUT, down && state[SDL_SCANCODE_LCTRL]);
        else if (sym == SDLK_b)
            nk_input_key(&m_Context, NK_KEY_TEXT_LINE_START, down && state[SDL_SCANCODE_LCTRL]);
        else if (sym == SDLK_e)
            nk_input_key(&m_Context, NK_KEY_TEXT_LINE_END, down && state[SDL_SCANCODE_LCTRL]);
        else if (sym == SDLK_UP)
            nk_input_key(&m_Context, NK_KEY_UP, down);
        else if (sym == SDLK_DOWN)
            nk_input_key(&m_Context, NK_KEY_DOWN, down);
        else if (sym == SDLK_LEFT)
        {
            if (state[SDL_SCANCODE_LCTRL])
                nk_input_key(&m_Context, NK_KEY_TEXT_WORD_LEFT, down);
            else nk_input_key(&m_Context, NK_KEY_LEFT, down);
        }
        else if (sym == SDLK_RIGHT)
        {
            if (state[SDL_SCANCODE_LCTRL])
                nk_input_key(&m_Context, NK_KEY_TEXT_WORD_RIGHT, down);
            else nk_input_key(&m_Context, NK_KEY_RIGHT, down);
        }
        else
        {
            return InputEventProcessState::NotHandled;
        }
        return InputEventProcessState::Handled;
    }
    else if (evt.type == SDL_MOUSEBUTTONDOWN || evt.type == SDL_MOUSEBUTTONUP)
    {
        /* mouse button */
        int down = evt.type == SDL_MOUSEBUTTONDOWN;
        const int x = evt.button.x, y = evt.button.y;
        if (evt.button.button == SDL_BUTTON_LEFT)
        {
            if (evt.button.clicks > 1)
                nk_input_button(&m_Context, NK_BUTTON_DOUBLE, x, y, down);
            nk_input_button(&m_Context, NK_BUTTON_LEFT, x, y, down);
        }
        else if (evt.button.button == SDL_BUTTON_MIDDLE)
            nk_input_button(&m_Context, NK_BUTTON_MIDDLE, x, y, down);
        else if (evt.button.button == SDL_BUTTON_RIGHT)
            nk_input_button(&m_Context, NK_BUTTON_RIGHT, x, y, down);
//        else return InputEventProcessState::NotHandled;
        return InputEventProcessState::Handled;
    }
    else if (evt.type == SDL_MOUSEMOTION)
    {
        /* mouse motion */
        if (m_Context.input.mouse.grabbed)
        {
            int x = (int)m_Context.input.mouse.prev.x, y = (int)m_Context.input.mouse.prev.y;
            nk_input_motion(&m_Context, x + evt.motion.xrel, y + evt.motion.yrel);
        }
        else
        {
            nk_input_motion(&m_Context, evt.motion.x, evt.motion.y);
        }
        return InputEventProcessState::Handled;
    }
    else if (evt.type == SDL_TEXTINPUT)
    {
        /* text input */
        nk_glyph glyph;
        memcpy(glyph, evt.text.text, NK_UTF_SIZE);
        nk_input_glyph(&m_Context, glyph);
        return InputEventProcessState::Handled;
    }
    else if (evt.type == SDL_MOUSEWHEEL)
    {
        /* mouse wheel */
        nk_input_scroll(&m_Context, nk_vec2((float)evt.wheel.x,(float)evt.wheel.y));
        return InputEventProcessState::Handled;
    }

    return InputEventProcessState::NotHandled;
}

nk_context* NkPolyhedron::GetContext()
{
    return &m_Context;
}
