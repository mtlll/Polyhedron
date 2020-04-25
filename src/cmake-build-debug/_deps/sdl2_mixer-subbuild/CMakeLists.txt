# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.16.5)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(sdl2_mixer-populate NONE)

include(ExternalProject)
ExternalProject_Add(sdl2_mixer-populate
                     "UPDATE_DISCONNECTED" "False" "URL" "https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.4.tar.gz" "DOWNLOAD_DIR" "/Users/micha/dev/cube/Polyhedron/src/cmake-build-debug/tmp"
                    SOURCE_DIR          "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2_mixer-2.0.4"
                    BINARY_DIR          "/Users/micha/dev/cube/Polyhedron/src/cmake-build-debug/_deps/sdl2_mixer-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)
