#include "nui.h"

namespace engine { namespace nui {

    std::unique_ptr<NkPolyhedron> NuklearPolyhedronDevice;

    void Initialize()
    {
        NuklearPolyhedronDevice.reset(new NkPolyhedron);
    }

    void Render()
    {
        NuklearPolyhedronDevice->Render();
    }

    void InputProcessBegin()
    {
        NuklearPolyhedronDevice->InputProcessBegin();
    }

    InputEventProcessState InputEvent(const SDL_Event &evt)
    {
        return NuklearPolyhedronDevice->InputEvent(evt);
    }
    void InputProcessEnd()
    {
        NuklearPolyhedronDevice->InputProcessEnd();
    }

    void Destroy()
    {
        NuklearPolyhedronDevice.reset();
    }

    nk_context *GetNKContext()
    {
        return NuklearPolyhedronDevice->GetContext();
    }

    namespace {
        enum {EASY, HARD};
        static int op = EASY;
        static float value = 0.6f;
        static int i =  20;
    }

    void DemoUI()
    {
        if (nk_begin(GetNKContext(), "Show", nk_rect(50, 50, 440, 440),
                     NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE)) {
            // fixed widget pixel width
            nk_layout_row_static(GetNKContext(), 60, 160, 1);
            if (nk_button_label(GetNKContext(), "button")) {
                // event handling
            }
            // fixed widget window ratio width
            nk_layout_row_dynamic(GetNKContext(), 30, 2);
            if (nk_option_label(GetNKContext(), "easy", op == EASY)) op = EASY;
            if (nk_option_label(GetNKContext(), "hard", op == HARD)) op = HARD;
            // custom widget pixel width
            nk_layout_row_begin(GetNKContext(), NK_STATIC, 30, 2);
            {
                nk_layout_row_push(GetNKContext(), 100);
                nk_label(GetNKContext(), "Volume:", NK_TEXT_LEFT);
                nk_layout_row_push(GetNKContext(), 220);
                nk_slider_float(GetNKContext(), 0, &value, 1.0f, 0.1f);
            }
            nk_layout_row_end(GetNKContext());
        }
        nk_end(GetNKContext());

    }
}
}