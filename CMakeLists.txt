project(DxLibForHTML5)

cmake_minimum_required(VERSION 3.13)



# Library Declaration

add_library(DxLib STATIC)
add_library(DxDrawFunc STATIC)
add_library(DxUseCLib STATIC)



# SubDirectories

add_subdirectory(HTML5)



# DxLib

target_include_directories(DxLib
    PUBLIC
        HTML5/
        extlib/freetype/include/
)

target_sources(DxLib
    PRIVATE
        DxArchive_.cpp
        DxASyncLoad.cpp
        DxBaseFunc.cpp
        DxBaseImage.cpp
        DxChar.cpp
        DxCharCodeTable.cpp
        DxFile.cpp
        DxFont.cpp
        DxGateway.cpp
        DxGraphics.cpp
        DxGraphicsFilter.cpp
        DxHandle.cpp
        DxHeap.cpp
        DxInput.cpp
        DxInputString.cpp
        DxLive2DCubism4.cpp
        DxLog.cpp
        DxMask.cpp
        DxMath.cpp
        DxMemImg.cpp
        DxMemory.cpp
        DxModel.cpp
        DxModelLoader0.cpp
        DxModelLoader1.cpp
        DxModelLoader2.cpp
        DxModelLoader3.cpp
        DxModelLoader4.cpp
        DxModelLoaderVMD.cpp
        DxModelRead.cpp
        DxMovie.cpp
        DxNetwork.cpp
        DxRingBuffer.cpp
        DxSoftImage.cpp
        DxSound.cpp
        DxSoundConvert.cpp
        DxSystem.cpp
        DxThread.cpp
)

set_target_properties(DxLib
    PROPERTIES 
        COMPILE_FLAGS "-s USE_FREETYPE=1 -s SIDE_MODULE=1 -s ALLOW_MEMORY_GROWTH=1"
        CXX_STANDARD 11
)

target_link_libraries(DxLib
    DxDrawFunc
)



# DxDrawFunc

target_sources(DxDrawFunc
    PRIVATE
        DxMemImgDrawFunction0.cpp
        DxMemImgDrawFunction1.cpp
        DxMemImgDrawFunction2.cpp
        DxMemImgDrawFunction3.cpp
)

set_target_properties(DxDrawFunc
    PROPERTIES 
        COMPILE_FLAGS "-s SIDE_MODULE=1 -s ALLOW_MEMORY_GROWTH=1"
        CXX_STANDARD 11
)



# DxUseCLib

target_include_directories(DxUseCLib
    PRIVATE 
        extlib/vorbis/lib/
        extlib/bullet3/src/
)

target_sources(DxUseCLib
    PRIVATE
        DxUseCLib.cpp
        DxUseCLibLive2DCubism4.cpp
        DxUseCLibOgg.cpp
        DxUseCLibPhysics.cpp
)

set_target_properties(DxUseCLib
    PROPERTIES 
        COMPILE_FLAGS "-s USE_OGG=1 -s USE_VORBIS=1 -s USE_LIBPNG=1 -s USE_LIBJPEG=1 -s USE_ZLIB=1 -s USE_BULLET=1 -s SIDE_MODULE=1 -s ALLOW_MEMORY_GROWTH=1"
        CXX_STANDARD 11
)

