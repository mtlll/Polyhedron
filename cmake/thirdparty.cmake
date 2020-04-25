
set(BUILD_SHARED_LIBS OFF)
set(DEPENDENCY_DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR}/tmp)
SET(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR})

include(FetchContent)
include(ExternalProject)

message("Fetching dependency: SDL2")
FetchContent_Declare(
    SDL2
    SOURCE_DIR          "${CMAKE_CURRENT_LIST_DIR}/thirdparty/SDL2-2.0.12"
    URL                 https://www.libsdl.org/release/SDL2-2.0.12.tar.gz
    DOWNLOAD_DIR        ${DEPENDENCY_DOWNLOAD_DIR}
    INSTALL_COMMAND     ""
)
FetchContent_GetProperties(SDL2)
if (NOT sdl2_POPULATED)
    source_group(TREE SDL2)
    FetchContent_MakeAvailable(SDL2)
endif()

message("Fetching dependency: SDL2_mixer")
FetchContent_Declare(
        SDL2_mixer
        SOURCE_DIR          "${CMAKE_CURRENT_LIST_DIR}/thirdparty/SDL2_mixer-2.0.4"
        URL                 https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.4.tar.gz
        DOWNLOAD_DIR        ${DEPENDENCY_DOWNLOAD_DIR}
        INSTALL_COMMAND     ""
)
FetchContent_GetProperties(SDL2_mixer)
if (NOT sdl2_mixer_POPULATED)
    source_group(TREE SDL2_mixer)
    file(COPY
        ${CMAKE_CURRENT_LIST_DIR}/SDL2_mixer-2.0.4_CMakeLists.txt
        DESTINATION
        ${CMAKE_CURRENT_LIST_DIR}/thirdparty/SDL2_mixer-2.0.4
    )
    file(RENAME
        ${CMAKE_CURRENT_LIST_DIR}/thirdparty/SDL2_mixer-2.0.4/SDL2_mixer-2.0.4_CMakeLists.txt
        ${CMAKE_CURRENT_LIST_DIR}/thirdparty/SDL2_mixer-2.0.4/CMakeLists.txt
    )
    FetchContent_MakeAvailable(SDL2_mixer)
endif()

find_package(OpenGL REQUIRED)

if (APPLE)
    find_library(COREAUDIO CoreAudio REQUIRED)
    find_library(AVFOUNDATION AVFoundation REQUIRED)
    find_library(COCOA Cocoa REQUIRED)
    find_library(COREFOUNDATION CoreFoundation REQUIRED)
    find_library(APPLICATIONSERVICES ApplicationServices REQUIRED)
    find_library(FOUNDATION Foundation REQUIRED)
    find_library(COREFOUNDATION CoreFoundation REQUIRED)
    find_library(AUDIOTOOLBOX AudioToolbox REQUIRED)
    find_library(BULLSHITLIB BullShitLib REQUIRED)
endif()

# message("Fetching dependency SDL2_image")
# FetchContent_Declare(
#     SDL2_IMAGE
#     SOURCE_DIR          ${CMAKE_CURRENT_LIST_DIR}/thirdparty/SDL2_image-2.0.5
#     URL                 https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.5.tar.gz
#     DOWNLOAD_DIR        ${DEPENDENCY_DOWNLOAD_DIR}
#     INSTALL_COMMAND     ""
# )
# FetchContent_GetProperties(SDL2_IMAGE)
# if (NOT sdl2_image_POPULATED)
#     file(COPY
#         ${CMAKE_CURRENT_LIST_DIR}/SDL2_Image-2.0.5_CMakeLists.txt
#         DESTINATION
#         ${CMAKE_CURRENT_LIST_DIR}/thirdparty/SDL2_image-2.0.5
#     )
#     file(RENAME
#         ${CMAKE_CURRENT_LIST_DIR}/thirdparty/SDL2_image-2.0.5/SDL2_Image-2.0.5_CMakeLists.txt
#         ${CMAKE_CURRENT_LIST_DIR}/thirdparty/SDL2_image-2.0.5/CMakeLists.txt
#     )
#     file(COPY
#         ${CMAKE_CURRENT_LIST_DIR}/jpeg-9b_CMakeLists.txt
#         DESTINATION
#         ${CMAKE_CURRENT_LIST_DIR}/thirdparty/SDL2_image-2.0.5/external/jpeg-9b
#     )
#     file(RENAME
#         ${CMAKE_CURRENT_LIST_DIR}/thirdparty/SDL2_image-2.0.5/external/jpeg-9b/jpeg-9b_CMakeLists.txt
#         ${CMAKE_CURRENT_LIST_DIR}/thirdparty/SDL2_image-2.0.5/external/jpeg-9b/CMakeLists.txt
#     )

#     FetchContent_Populate(SDL2_IMAGE)
#     add_subdirectory(${sdl2_image_SOURCE_DIR} ${sdl2_image_BINARY_DIR})
# endif()

message("Fetching libjpeg")
FetchContent_Declare(
    LIBJPEG
    SOURCE_DIR          ${CMAKE_CURRENT_LIST_DIR}/thirdparty/libjpeg
    GIT_REPOSITORY      https://github.com/LuaDist/libjpeg.git
    DOWNLOAD_DIR        ${DEPENDENCY_DOWNLOAD_DIR}
    INSTALL_COMMAND     ""
)
FetchContent_GetProperties(LIBJPEG)
if (NOT libjpeg_POPULATED)
    source_group(TREE LIBJPEG)
    FetchContent_MakeAvailable(LIBJPEG)
endif()

message("Fetching libpng")
FetchContent_Declare(
    LIBPNG
    SOURCE_DIR          ${CMAKE_CURRENT_LIST_DIR}/thirdparty/libpng
    URL                 http://prdownloads.sourceforge.net/libpng/libpng-1.6.37.tar.gz?download
    DOWNLOAD_DIR        ${DEPENDENCY_DOWNLOAD_DIR}
    INSTALL_COMMAND     ""
)
FetchContent_GetProperties(LIBPNG)
if (NOT libpng_POPULATED)
    source_group(TREE LIBPNG)
    FetchContent_MakeAvailable(LIBPNG)
endif()

#message("Fetching Box2D")
#FetchContent_Declare(
#    BOX2D
#    SOURCE_DIR          ${CMAKE_CURRENT_LIST_DIR}/thirdparty/Box2D
#    GIT_REPOSITORY      https://github.com/erincatto/box2d.git
#    DOWNLOAD_DIR        ${DEPENDENCY_DOWNLOAD_DIR}
#    INSTALL_COMMAND     ""
#)
#FetchContent_GetProperties(BOX2D)
#if (NOT box2d_POPULATED)
#    set(BOX2D_BUILD_UNIT_TESTS OFF CACHE BOOL "OFF" FORCE)
#    set(BOX2D_BUILD_TESTBED OFF CACHE BOOL "OFF" FORCE)
#    set(BOX2D_BUILD_DOCS OFF CACHE BOOL "OFF" FORCE)
#    source_group(TREE BOX2D)
#    FetchContent_MakeAvailable(BOX2D)
#endif()

message("Fetching nothings/STB")
FetchContent_Declare(
    STB
    SOURCE_DIR          ${CMAKE_CURRENT_LIST_DIR}/thirdparty/STB
    GIT_REPOSITORY      https://github.com/nothings/stb.git
    DOWNLOAD_DIR        ${DEPENDENCY_DOWNLOAD_DIR}
    INSTALL_COMMAND     ""
)
FetchContent_GetProperties(STB)
if (NOT stb_POPULATED)
    FetchContent_Populate(STB)
    source_group(TREE BOX2D)
    add_definitions(-DSTB_IMAGE_IMPLEMENTATION)
endif()

list(APPEND THIRDPARTY_INCLUDE_DIRS
    "${SDL2_BINARY_DIR}/include"
    "${SDL2_SOURCE_DIR}/include"
    ${OPENGL_INCLUDE_DIRS}
#    ${stb_SOURCE_DIR}
    ${libjpeg_SOURCE_DIR}
    ${libpng_SOURCE_DIR}
)

list(APPEND THIRDPARTY_LINK_DIRS
    "${SDL2_BINARY_DIR}/$<CONFIG>"
)

list(APPEND THIRDPARTY_LINK_LIBS
    SDL2-static
    SDL2main
#    glm
#    box2d
    ${COREFOUNDATION}
    ${FOUNDATION}
    ${OPENGL_LIBRARIES}
)
