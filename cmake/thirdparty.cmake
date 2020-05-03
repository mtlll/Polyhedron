
set(BUILD_SHARED_LIBS OFF)
set(DEPENDENCY_DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR}/tmp)
SET(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/thirdparty)

include(FetchContent)
include(ExternalProject)

message("Fetching dependency: SDL2")
FetchContent_Declare(
    SDL2
    SOURCE_DIR          "${CMAKE_CURRENT_BINARY_DIR}/thirdparty_sources/SDL2-2.0.12"
    URL                 https://www.libsdl.org/release/SDL2-2.0.12.tar.gz
    DOWNLOAD_DIR        ${DEPENDENCY_DOWNLOAD_DIR}
    INSTALL_COMMAND     ""
)
FetchContent_GetProperties(SDL2)
if (NOT sdl2_POPULATED)
    source_group(TREE SDL2)
    FetchContent_MakeAvailable(SDL2)
endif()

message("Fetching dependency: OGG")
FetchContent_Declare(
        OGG
        SOURCE_DIR          "${CMAKE_CURRENT_BINARY_DIR}/thirdparty_sources/libogg-1.3.4"
        URL                 http://downloads.xiph.org/releases/ogg/libogg-1.3.4.tar.gz
        DOWNLOAD_DIR        ${DEPENDENCY_DOWNLOAD_DIR}
        INSTALL_COMMAND     ""
)
FetchContent_GetProperties(OGG)
if (NOT ogg_POPULATED)
    source_group(TREE OGG)
    FetchContent_Populate(OGG)
    execute_process(COMMAND
            cmake -E chdir "${CMAKE_CURRENT_BINARY_DIR}/thirdparty_sources/libogg-1.3.4"
            patch -p0 -i "${CMAKE_CURRENT_LIST_DIR}/patch-libogg-add-stdint-h.diff"
        RESULT_VARIABLE RESULT_PATCH
    )
    message(STATUS "Patching libogg: ${RESULT_PATCH}, SOURCE DIR: ${CMAKE_CURRENT_BINARY_DIR}/thirdparty_sources/libogg-1.3.4")

    add_subdirectory(${ogg_SOURCE_DIR} ${ogg_BINARY_DIR})
    FetchContent_MakeAvailable(OGG)
    set(OGG_INCLUDE_DIRS "${ogg_SOURCE_DIR}/include" "${ogg_BINARY_DIR}/include")
    set(OGG_LIBRARIES ogg)
    set(OGG_INCLUDE_DIR ${OGG_INCLUDE_DIRS})
    set(OGG_LIBRARY ${OGG_LIBRARIES})
endif()

message("Fetching dependency: Vorbis")
FetchContent_Declare(
        VORBIS
        SOURCE_DIR          "${CMAKE_CURRENT_BINARY_DIR}/thirdparty_sources/libvorbis-1.3.6"
        URL                 https://github.com/xiph/vorbis/archive/v1.3.6.tar.gz
        DOWNLOAD_DIR        ${DEPENDENCY_DOWNLOAD_DIR}
        INSTALL_COMMAND     ""
)
FetchContent_GetProperties(VORBIS)
if (NOT vorbis_POPULATED)
    source_group(TREE VORBIS)
    FetchContent_Populate(VORBIS)
    execute_process(COMMAND
        cmake -E chdir "${CMAKE_CURRENT_BINARY_DIR}/thirdparty_sources/libvorbis-1.3.6"
        patch -p0 -i "${CMAKE_CURRENT_LIST_DIR}/patch-libvorbis-CMakeLists.txt.diff"
        RESULT_VARIABLE RESULT_PATCH1
    )
    execute_process(COMMAND
        cmake -E chdir "${CMAKE_CURRENT_BINARY_DIR}/thirdparty_sources/libvorbis-1.3.6"
        patch -p0 -i "${CMAKE_CURRENT_LIST_DIR}/patch-libvorbis-lib-CMakeLists.txt.diff"
        RESULT_VARIABLE RESULT_PATCH2
    )
    message(STATUS "Patching libvorbis: 1: ${RESULT_PATCH1}, 2: ${RESULT_PATCH2}, SOURCE DIR: ${CMAKE_CURRENT_BINARY_DIR}/thirdparty_sources/libogg-1.3.4")

    FetchContent_MakeAvailable(VORBIS)
endif()

if (NOT ANDROID)
    message("Fetching dependency: Flac")
    FetchContent_Declare(
            FLAC
            SOURCE_DIR          "${CMAKE_CURRENT_BINARY_DIR}/thirdparty_sources/flac-1.3.3"
            URL                 https://github.com/xiph/flac/archive/1.3.3.tar.gz
            DOWNLOAD_DIR        ${DEPENDENCY_DOWNLOAD_DIR}
            INSTALL_COMMAND     ""
    )
    FetchContent_GetProperties(FLAC)
    if (NOT flac_POPULATED)
        source_group(TREE FLAC)
        set(BUILD_EXAMPLES OFF)
        set(BUILD_TESTING OFF)
        set(BUILD_CXXLIBS OFF)
        set(ENABLE_64_BIT_WORDS ON)
        FetchContent_MakeAvailable(FLAC)
    endif()
endif()

message("Fetching dependency: SDL2_mixer")
FetchContent_Declare(
        SDL2_mixer
        SOURCE_DIR          "${CMAKE_CURRENT_BINARY_DIR}/thirdparty_sources/SDL2_mixer-2.0.4"
        URL                 https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.4.tar.gz
        DOWNLOAD_DIR        ${DEPENDENCY_DOWNLOAD_DIR}
        INSTALL_COMMAND     ""
)
FetchContent_GetProperties(SDL2_mixer)
if (NOT sdl2_mixer_POPULATED)
    source_group(TREE SDL2_mixer)
    configure_file(
        "${CMAKE_CURRENT_LIST_DIR}/SDL2_mixer-2.0.4_CMakeLists.txt"
        "${CMAKE_CURRENT_BINARY_DIR}/thirdparty_sources/SDL2_mixer-2.0.4/CMakeLists.txt"
        COPYONLY
    )
    set(SDL_MIXER_INCLUDES ${sdl2_SOURCE_DIR}/include)
    set(SDL_MIXER_LIBRARIES SDL2-static)
    FetchContent_MakeAvailable(SDL2_mixer)
endif()

message("Fetching dependency SDL2_image")
FetchContent_Declare(
    SDL2_IMAGE
    SOURCE_DIR          ${CMAKE_CURRENT_BINARY_DIR}/thirdparty_sources/SDL2_image-2.0.5
    URL                 https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.5.tar.gz
    DOWNLOAD_DIR        ${DEPENDENCY_DOWNLOAD_DIR}
    INSTALL_COMMAND     ""
)
FetchContent_GetProperties(SDL2_IMAGE)
if (NOT sdl2_image_POPULATED)
    configure_file(
        "${CMAKE_CURRENT_LIST_DIR}/jpeg-9b_CMakeLists.txt"
        "${CMAKE_CURRENT_BINARY_DIR}/thirdparty_sources/SDL2_image-2.0.5/external/jpeg-9b/CMakeLists.txt"
        COPYONLY
    )
    configure_file(
        "${CMAKE_CURRENT_LIST_DIR}/SDL2_Image-2.0.5_CMakeLists.txt"
        "${CMAKE_CURRENT_BINARY_DIR}/thirdparty_sources/SDL2_image-2.0.5/CMakeLists.txt"
        COPYONLY
    )
    FetchContent_Populate(SDL2_IMAGE)
    add_subdirectory(${sdl2_image_SOURCE_DIR} ${sdl2_image_BINARY_DIR})
endif()
#
#message("Fetching libjpeg")
#FetchContent_Declare(
#    LIBJPEG
#    SOURCE_DIR          ${CMAKE_CURRENT_BINARY_DIR}/thirdparty_sources/libjpeg
#    GIT_REPOSITORY      https://github.com/LuaDist/libjpeg.git
#    DOWNLOAD_DIR        ${DEPENDENCY_DOWNLOAD_DIR}
#    INSTALL_COMMAND     ""
#)
#FetchContent_GetProperties(LIBJPEG)
#if (NOT libjpeg_POPULATED)
#    source_group(TREE LIBJPEG)
#    FetchContent_MakeAvailable(LIBJPEG)
#endif()
#
#message("Fetching libpng")
#FetchContent_Declare(
#    LIBPNG
#    SOURCE_DIR          ${CMAKE_CURRENT_BINARY_DIR}/thirdparty_sources/libpng
#    URL                 http://prdownloads.sourceforge.net/libpng/libpng-1.6.37.tar.gz?download
#    DOWNLOAD_DIR        ${DEPENDENCY_DOWNLOAD_DIR}
#    INSTALL_COMMAND     ""
#)
#FetchContent_GetProperties(LIBPNG)
#if (NOT libpng_POPULATED)
#    source_group(TREE LIBPNG)
#    FetchContent_MakeAvailable(LIBPNG)
#endif()

#message("Fetching nothings/STB")
#FetchContent_Declare(
#    STB
#    SOURCE_DIR          ${CMAKE_CURRENT_BINARY_DIR}/thirdparty_sources/STB
#    GIT_REPOSITORY      https://github.com/nothings/stb.git
#    DOWNLOAD_DIR        ${DEPENDENCY_DOWNLOAD_DIR}
#    INSTALL_COMMAND     ""
#)
#FetchContent_GetProperties(STB)
#if (NOT stb_POPULATED)
#    FetchContent_Populate(STB)
#    source_group(TREE BOX2D)
#    add_definitions(-DSTB_IMAGE_IMPLEMENTATION)
#endif()

list(APPEND THIRDPARTY_INCLUDE_DIRS
)

list(APPEND THIRDPARTY_LINK_DIRS
)

list(APPEND THIRDPARTY_LIBRARIES
    SDL2-static
#    SDL2main
    SDL2_image
    SDL2_mixer
#    mpg123
)

if (APPLE)
    find_library(COREFOUNDATION CoreFoundation REQUIRED)
    find_library(FOUNDATION Foundation REQUIRED)

    find_library(COREAUDIO CoreAudio REQUIRED)
    find_library(COREVIDEO CoreVideo REQUIRED)
    find_library(AVFOUNDATION AVFoundation REQUIRED)
    find_library(COCOA Cocoa REQUIRED)
    find_library(APPLICATIONSERVICES ApplicationServices REQUIRED)
    find_library(AUDIOTOOLBOX AudioToolbox REQUIRED)
    find_library(FORCEFEEDBACK ForceFeedback REQUIRED)
    find_library(IOKIT IOKit REQUIRED)
    find_library(CARBON Carbon REQUIRED)

    list(APPEND THIRDPARTY_LIBRARIES
        ${COREFOUNDATION}
        ${FOUNDATION}
        ${COREAUDIO}
        ${COREVIDEO}
        ${AVFOUNDATION}
        ${COCOA}
        ${APPLICATIONSERVICES}
        ${AUDIOTOOLBOX}
        ${FORCEFEEDBACK}
        ${IOKIT}
        ${CARBON}
    )
endif()

if (ANDROID)
    list(APPEND THIRDPARTY_LIBRARIES
        log
        GLESv2
        EGL
        android
    )
endif()


if (NOT ANDROID)
    find_package(OpenGL REQUIRED)
    find_package(Iconv REQUIRED)

    list(APPEND THIRDPARTY_LIBRARIES
        ${OPENGL_LIBRARIES}
        ${Iconv_LIBRARY}
    )
endif()