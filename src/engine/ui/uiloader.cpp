#include "shared/nukeui/nukeui.h"

namespace engine {
    namespace nukeui {
        class NukeUI {
            // Static context related to NukeUI.
            static nk_context *ctx;

            //
            // Creates the Nuklear UI Context.
            //
            // Important since it determines theme/skin as well as font.
            //
            bool CreateContext() {
                ctx = nk_init_default(ctx, NULL);
                if (ctx) // Use default style for now.
                    nk_style_default(ctx);
                return ctx == NULL ? false : true;
            }

            void OpenFrame() {
                
            }

            void RenderFrame(void *func) {
                
            }

            //
            // Has to be called before swapbuffers, somewhere near
            // the end of the rendering frame. (Probably dumps out all
            // the glDraw functions.)
            //
            void CloseFrame() {
                nk_clear(ctx);
            }
        };
        static NukeUI ui; // The UI instance.
    }; // NukeUI
}; // Engine