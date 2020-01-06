#include "engine/ui/uimain.h"
#include "shared/nukeui/nukeui.h"

namespace engine {
    namespace nukeui {
        // Static external global mofucking NukeUI, ur only instance ffs.
        NukeUI ui; // The UI instance.

        //
        // Creates the Nuklear UI Context.
        //
        // Important since it determines theme/skin as well as font.
        //
        bool NukeUI::CreateContext() {
            nk_init_default(ctx, NULL);
            if (ctx) // Use default style for now.
                nk_style_default(ctx);
            return ctx == NULL ? false : true;
        }

        //
        // Opens up the frame, aka prepares nuklear UI for rendering.
        //
        void NukeUI::OpenFrame() {
            
        }

        //
        // Renders a goddamn nuklear UI frame for fuck sake.
        //
        void NukeUI::RenderFrame(void *func) {
            
        }

        //
        // Has to be called before swapbuffers, somewhere near
        // the end of the rendering frame. (Probably dumps out all
        // the glDraw functions.)
        //
        void NukeUI::CloseFrame() {
            nk_clear(ctx);
        }
    }; // NukeUI
}; // Engine