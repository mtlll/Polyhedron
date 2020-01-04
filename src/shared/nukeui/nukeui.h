#pragma once

/// NK_PRIVATE                      | If defined declares all functions as static, so they can only be accessed inside the file that contains the implementation
#define NK_INCLUDE_FIXED_TYPES          //| If defined it will include header `<stdint.h>` for fixed sized types otherwise nuklear tries to select the correct type. If that fails it will throw a compiler error and you have to select the correct types yourself.
#define NK_INCLUDE_DEFAULT_ALLOCATOR    //| If defined it will include header `<stdlib.h>` and provide additional functions to use this library without caring for memory allocation control and therefore ease memory management.
#define NK_INCLUDE_STANDARD_IO          //| If defined it will include header `<stdio.h>` and provide additional functions depending on file loading.
#define NK_INCLUDE_STANDARD_VARARGS     //| If defined it will include header <stdio.h> and provide additional functions depending on file loading.
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT //| Defining this adds a vertex draw command list backend to this library, which allows you to convert queue commands into vertex draw commands. This is mainly if you need a hardware accessible format for OpenGL, DirectX, Vulkan, Metal,...
#define NK_INCLUDE_FONT_BAKING          //| Defining this adds `stb_truetype` and `stb_rect_pack` implementation to this library and provides font baking and rendering. If you already have font handling or do not want to use this font handler you don't have to define it.
/// NK_INCLUDE_DEFAULT_FONT             //| Defining this adds the default font: ProggyClean.ttf into this library which can be loaded into a font atlas and allows using this library without having a truetype font
#define NK_INCLUDE_COMMAND_USERDATA     //| Defining this adds a userdata pointer into each command. Can be useful for example if you want to provide custom shaders depending on the used widget. Can be combined with the style structures.
#define NK_BUTTON_TRIGGER_ON_RELEASE    //| Different platforms require button clicks occurring either on buttons being pressed (up to down) or released (down to up). By default this library will react on buttons being pressed, but if you define this it will only trigger if a button is released.
#define NK_ZERO_COMMAND_MEMORY          //| Defining this will zero out memory for each drawing command added to a drawing queue (inside nk_command_buffer_push). Zeroing command memory is very useful for fast checking (using memcmp) if command buffers are equal and avoid drawing frames when nothing on screen has changed since previous frame.
#define NK_UINT_DRAW_INDEX              //| Defining this will set the size of vertex index elements when using NK_VERTEX_BUFFER_OUTPUT to 32bit instead of the default of 16bit
/// NK_KEYSTATE_BASED_INPUT         | Define this if your backend uses key state for each frame rather than key press/release events
///

#define NK_IMPLEMENTATION
#include "../../ext/Nuklear/nuklear.h"