# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.16.5)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(libpng-populate NONE)

include(ExternalProject)
ExternalProject_Add(libpng-populate
                     "UPDATE_DISCONNECTED" "False" "URL" "http://prdownloads.sourceforge.net/libpng/libpng-1.6.37.tar.gz?download" "DOWNLOAD_DIR" "/Users/micha/dev/cube/Polyhedron/src/cmake-build-debug/tmp"
                    SOURCE_DIR          "/Users/micha/dev/cube/Polyhedron/cmake/thirdparty/libpng"
                    BINARY_DIR          "/Users/micha/dev/cube/Polyhedron/src/cmake-build-debug/_deps/libpng-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)
