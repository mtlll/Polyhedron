#pragma once

#include "shared/nukeui/nukeui.h"

// compile die shit
namespace engine
{
    namespace nukeui
    {
        class NukeUI
        {
        private:
            // Static context related to NukeUI.
            static nk_context *ctx;

        public:
            //
            // Creates the Nuklear UI Context.
            //
            // Important since it determines theme/skin as well as font.
            //
            bool CreateContext();

            //
            // Opens up the frame, aka prepares nuklear UI for rendering.
            //
            void OpenFrame();

            //
            // Renders a goddamn nuklear UI frame for fuck sake.
            //
            void RenderFrame(void *func);

            //
            // Has to be called before swapbuffers, somewhere near
            // the end of the rendering frame. (Probably dumps out all
            // the glDraw functions.)
            //
            void CloseFrame();
        };
    }; // namespace nukeui
}; // namespace engine