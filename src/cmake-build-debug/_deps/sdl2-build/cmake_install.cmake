# Install script for directory: /Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/micha/dev/cube/Polyhedron/src/cmake-build-debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/micha/dev/cube/Polyhedron/src/cmake-build-debug/_deps/sdl2-build/libSDL2d.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2d.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2d.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2d.a")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/Users/micha/dev/cube/Polyhedron/src/cmake-build-debug/_deps/sdl2-build/libSDL2maind.a")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2maind.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2maind.a")
    execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libSDL2maind.a")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2Targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2Targets.cmake"
         "/Users/micha/dev/cube/Polyhedron/src/cmake-build-debug/_deps/sdl2-build/CMakeFiles/Export/lib/cmake/SDL2/SDL2Targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2Targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2/SDL2Targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "/Users/micha/dev/cube/Polyhedron/src/cmake-build-debug/_deps/sdl2-build/CMakeFiles/Export/lib/cmake/SDL2/SDL2Targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES "/Users/micha/dev/cube/Polyhedron/src/cmake-build-debug/_deps/sdl2-build/CMakeFiles/Export/lib/cmake/SDL2/SDL2Targets-debug.cmake")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/SDL2" TYPE FILE FILES
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/SDL2Config.cmake"
    "/Users/micha/dev/cube/Polyhedron/src/cmake-build-debug/SDL2ConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL2" TYPE FILE FILES
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_assert.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_atomic.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_audio.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_bits.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_blendmode.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_clipboard.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_config_android.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_config_iphoneos.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_config_macosx.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_config_minimal.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_config_os2.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_config_pandora.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_config_psp.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_config_windows.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_config_winrt.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_config_wiz.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_copying.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_cpuinfo.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_egl.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_endian.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_error.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_events.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_filesystem.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_gamecontroller.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_gesture.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_haptic.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_hints.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_joystick.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_keyboard.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_keycode.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_loadso.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_log.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_main.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_messagebox.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_metal.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_mouse.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_mutex.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_name.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_opengl.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_opengl_glext.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_opengles.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_opengles2.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_opengles2_gl2.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_opengles2_gl2ext.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_opengles2_gl2platform.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_opengles2_khrplatform.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_pixels.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_platform.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_power.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_quit.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_rect.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_render.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_revision.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_rwops.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_scancode.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_sensor.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_shape.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_stdinc.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_surface.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_system.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_syswm.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_test.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_test_assert.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_test_common.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_test_compare.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_test_crc32.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_test_font.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_test_fuzzer.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_test_harness.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_test_images.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_test_log.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_test_md5.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_test_memory.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_test_random.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_thread.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_timer.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_touch.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_types.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_version.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_video.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/SDL_vulkan.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/begin_code.h"
    "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/include/close_code.h"
    "/Users/micha/dev/cube/Polyhedron/src/cmake-build-debug/_deps/sdl2-build/include/SDL_config.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/Users/micha/dev/cube/Polyhedron/src/cmake-build-debug/_deps/sdl2-build/sdl2.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM FILES "/Users/micha/dev/cube/Polyhedron/src/cmake-build-debug/_deps/sdl2-build/sdl2-config")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/micha/dev/cube/Polyhedron/src/cmake-build-debug/share/aclocal/sdl2.m4")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/micha/dev/cube/Polyhedron/src/cmake-build-debug/share/aclocal" TYPE FILE FILES "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12/sdl2.m4")
endif()

