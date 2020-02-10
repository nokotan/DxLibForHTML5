project(DxLibForHTML5)

cmake_minimum_required(VERSION 2.8)

include_directories(
	./
	HTML5/
    extlib/vorbis/include/
    extlib/freetype/include/
)

link_directories(
    
)

file(GLOB DXPORTLIB_SOURCES
    *.cpp
	HTML5/*.cpp
)

set(USE_LIBLALIES
    "-s USE_OGG=1 -s USE_VORBIS=1 -s USE_LIBPNG=1 -s USE_ZLIB=1 -s USE_SDL=0 -s USE_SDL_IMAGE=0 -s USE_SDL_TTF=0 -s USE_SDL_NET=0 -s USE_SDL_MIXER=0 "
)

set(CXX_CONFIG
    "-Wall -std=c++11 "
)

set(DEBUG_CONFIG
    "-s ASSERTIONS=1 "
)

set(DEPLOY_CONFIG
    "-s SIDE_MODULE=1 -s ALLOW_MEMORY_GROWTH=1 "
)

string(APPEND CMAKE_CXX_FLAGS ${USE_LIBLALIES} ${CXX_CONFIG} ${DEBUG_CONFIG} ${DEPLOY_CONFIG})

add_library(DxLib STATIC ${DXPORTLIB_SOURCES})
