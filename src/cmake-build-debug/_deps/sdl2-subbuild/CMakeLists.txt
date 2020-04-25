# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.16.5)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(sdl2-populate NONE)

include(ExternalProject)
ExternalProject_Add(sdl2-populate
                     "UPDATE_DISCONNECTED" "False" "URL" "https://www.libsdl.org/release/SDL2-2.0.12.tar.gz" "DOWNLOAD_DIR" "/Users/micha/dev/cube/Polyhedron/src/cmake-build-debug/tmp"
                    SOURCE_DIR          "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/SDL2-2.0.12"
                    BINARY_DIR          "/Users/micha/dev/cube/Polyhedron/src/cmake-build-debug/_deps/sdl2-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)
