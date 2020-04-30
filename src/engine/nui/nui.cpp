#include "engine.h"
#include "glexts.h"

#include "nui.h"

/// Nuklear UI SDL2 GL3 Implementation.
#define MAX_NUI_VERTEX_MEMORY 512 * 1024
#define MAX_NUI_ELEMENT_MEMORY 128 * 1024
#define NK_IMPLEMENTATION
#define NK_INCLUDE_FIXED_TYPES              //| If defined it will include header `<stdint.h>` for fixed sized types otherwise nuklear tries to select the correct type. If that fails it will throw a compiler error and you have to select the correct types yourself.
#define NK_INCLUDE_DEFAULT_ALLOCATOR    //| If defined it will include header `<stdlib.h>` and provide additional functions to use this library without caring for memory allocation control and therefore ease memory management.
#define NK_INCLUDE_STANDARD_IO          //| If defined it will include header `<stdio.h>` and provide additional functions depending on file loading.
#define NK_INCLUDE_STANDARD_VARARGS     //| If defined it will include header <stdio.h> and provide additional functions depending on file loading.
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT //| Defining this adds a vertex draw command list backend to this library, which allows you to convert queue commands into vertex draw commands. This is mainly if you need a hardware accessible format for OpenGL, DirectX, Vulkan, Metal,...
#define NK_INCLUDE_FONT_BAKING          //| Defining this adds `stb_truetype` and `stb_rect_pack` implementation to this library and provides font baking and rendering. If you already have font handling or do not want to use this font handler you don't have to define it.
#define NK_INCLUDE_DEFAULT_FONT         //| Defining this adds the default font: ProggyClean.ttf into this library which can be loaded into a font atlas and allows using this library without having a truetype font
//#define NK_INCLUDE_COMMAND_USERDATA     //| Defining this adds a userdata pointer into each command. Can be useful for example if you want to provide custom shaders depending on the used widget. Can be combined with the style structures.
//#define NK_BUTTON_TRIGGER_ON_RELEASE    //| Different platforms require button clicks occurring either on buttons being pressed (up to down) or released (down to up). By default this library will react on buttons being pressed, but if you define this it will only trigger if a button is released.
#define NK_ZERO_COMMAND_MEMORY          //| Defining this will zero out memory for each drawing command added to a drawing queue (inside nk_command_buffer_push). Zeroing command memory is very useful for fast checking (using memcmp) if command buffers are equal and avoid drawing frames when nothing on screen has changed since previous frame.
#define NK_UINT_DRAW_INDEX              //| Defining this will set the size of vertex index elements when using NK_VERTEX_BUFFER_OUTPUT to 32bit instead of the default of 16bit
/// #define NK_KEYSTATE_BASED_INPUT         //| Define this if your backend uses key state for each frame rather than key press/release events
#define STB_TRUETYPE_IMPLEMENTATION
#define STB_RECT_PACK_IMPLEMENTATION
#define NK_MEMSET memset
#include <nuklear.h>
#include <nuklear_sdl_gl3.h>


namespace engine { namespace nui {

// Nuklear UI Default context, and background color.
nk_context *nui_ctx = nullptr;
nk_colorf nui_bg = {0.3f, 0.3f, 0.3f, 0.3f};

int Initialize(SDL_Window *wnd) {
	// Initialize the SDL2/GL3 binding to the SDL Window Context.
//    glCheckError(glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS));
//    glCheckError(glPushAttrib(GL_ALL_ATTRIB_BITS));
    nui_ctx = nk_sdl_init(wnd);

	// Load Fonts: if none of these are loaded a default font will be used
	// Load Cursor: if you uncomment cursor loading please hide the cursor
	{
		nk_font_atlas *atlas;
		nk_sdl_font_stash_begin(&atlas);
		nk_font *default_engine = nk_font_atlas_add_from_file(atlas, "media/interface/font/default.ttf", 14, nullptr);
		//struct nk_font *roboto = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Roboto-Regular.ttf", 16, 0);
		//struct nk_font *future = nk_font_atlas_add_from_file(atlas, "../../../extra_font/kenvector_future_thin.ttf", 13, 0);
		//struct nk_font *clean = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyClean.ttf", 12, 0);
		//struct nk_font *tiny = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyTiny.ttf", 10, 0);
		//struct nk_font *cousine = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Cousine-Regular.ttf", 13, 0);
		nk_sdl_font_stash_end();
		nk_style_load_all_cursors(nui_ctx, atlas->cursors);
		nk_style_set_font(nui_ctx, &default_engine->handle);
	}

	// Set the style of Nuklear UI.
	set_style(nui_ctx, THEME_DARK);
	//set_style(ctx, THEME_WHITE);
	//set_style(ctx, THEME_RED);
	//set_style(ctx, THEME_BLUE);
//    glCheckError(lglPopAttrib());
//    glCheckError(gPopClientAttrib());

	return 0;
}

int Render() {
//    glCheckError(glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS));
//    glCheckError(glPushAttrib(GL_ALL_ATTRIB_BITS));
    nk_sdl_render(NK_ANTI_ALIASING_ON, MAX_NUI_VERTEX_MEMORY, MAX_NUI_ELEMENT_MEMORY);
//    glCheckError(glPopAttrib());
//    glCheckError(glPopClientAttrib());

	return 0;
}

int UserInputBeginPoll() {
	nk_input_begin(nui_ctx);
	return 0;
}
int UserInputPolLEvent(const SDL_Event &evt) {
	nk_sdl_handle_event((SDL_Event*)&evt);

	return 0;
}
int UserInputEndPoll() {
	nk_input_end(nui_ctx);
	return 0;
}

int Destroy() {
	// Shutdown NK_SDL_GL3
	nk_sdl_shutdown();

	return 0;
}

nk_context *GetNKContext() {
	return nui_ctx;
}

}
}