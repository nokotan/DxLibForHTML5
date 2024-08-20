cmake_minimum_required(VERSION 3.13)

project(DxLibForHTML5)

# Library Configuration

option(DXLIB_BUILD_SHARED_MAIN "Build plugin-style DxLib application loader." OFF)



# Library Declaration

add_library(DxLib STATIC)
add_library(DxDrawFunc STATIC)
add_library(DxUseCLib STATIC)



# SubDirectories

add_subdirectory(HTML5)



# DxLib

target_include_directories(DxLib
    PRIVATE
        HTML5/
        ../extlib/freetype/include/
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

target_compile_definitions(DxLib
PRIVATE
    PROXY_TO_PTHREAD
)

set_target_properties(DxLib
    PROPERTIES 
        COMPILE_FLAGS "-sUSE_FREETYPE=1 -pthread -fwasm-exceptions"
        CXX_STANDARD 11
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
        COMPILE_FLAGS "-pthread -fwasm-exceptions"
        CXX_STANDARD 11
)



# DxUseCLib

target_include_directories(DxUseCLib
    PRIVATE 
        ../extlib/vorbis/lib/
        ../extlib/bullet3/src/
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
        COMPILE_FLAGS "-sUSE_OGG=1 -sUSE_VORBIS=1 -sUSE_LIBPNG=1 -sUSE_LIBJPEG=1 -sUSE_ZLIB=1 -sUSE_BULLET=1 -pthread -fwasm-exceptions"
        CXX_STANDARD 11
)



# DxLibSharedMain

add_executable(DxLibSharedMain EXCLUDE_FROM_ALL
    Empty.cpp
)

target_link_libraries(DxLibSharedMain
    DxLib
    DxDrawFunc
    DxUseCLib
)

set_target_properties(DxLibSharedMain
    PROPERTIES 
        COMPILE_FLAGS "-s USE_FREETYPE=1 -s MAIN_MODULE=1"
        LINK_FLAGS "-sERROR_ON_UNDEFINED_SYMBOLS=0 -sUSE_FREETYPE=1 -sUSE_BULLET=1 -sUSE_VORBIS=1 -sUSE_OGG=1 -sUSE_LIBPNG=1 -sUSE_ZLIB=1 -sFULL_ES2=1 -sALLOW_MEMORY_GROWTH=1 -sMAIN_MODULE=1 -sDECLARE_ASM_MODULE_EXPORTS=0"
        CXX_STANDARD 11
)



if (DXLIB_BUILD_SHARED_MAIN)
    target_compile_options(DxLib
        PRIVATE
            "-sSIDE_MODULE=1"
    )

    target_compile_options(DxDrawFunc
        PRIVATE
            "-sSIDE_MODULE=1"
    )

    target_compile_options(DxUseCLib
        PRIVATE
            "-sSIDE_MODULE=1"
    )

    set_target_properties(DxLibSharedMain
    PROPERTIES
        EXCLUDE_FROM_ALL OFF
    )
endif()



include(GNUInstallDirs)

if ("${CMAKE_CXX_FLAGS}" MATCHES "-flto")
    set(LIBDIR "${CMAKE_INSTALL_LIBDIR}/wasm32-emscripten/lto")
else()
    set(LIBDIR "${CMAKE_INSTALL_LIBDIR}/wasm32-emscripten")
endif()

install(TARGETS DxLib
  EXPORT DxLibExport
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${LIBDIR}
  ARCHIVE DESTINATION ${LIBDIR}
)

install(EXPORT DxLibExport
  FILE DxLibConfig.cmake
  DESTINATION share/cmake/DxLibConfig/
)

install(TARGETS DxDrawFunc
  EXPORT DxDrawFuncExport
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${LIBDIR}
  ARCHIVE DESTINATION ${LIBDIR}
)

install(EXPORT DxDrawFuncExport
  FILE DxDrawFuncConfig.cmake
  DESTINATION share/cmake/DxDrawFuncConfig/
)

install(TARGETS DxUseCLib
  EXPORT DxUseCLibExport
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${LIBDIR}
  ARCHIVE DESTINATION ${LIBDIR}
)

install(EXPORT DxUseCLibExport
  FILE DxUseCLibConfig.cmake
  DESTINATION share/cmake/DxUseCLibConfig/
)

install(
    FILES
        ${PROJECT_SOURCE_DIR}/DxLib.h 
        ${PROJECT_SOURCE_DIR}/DxCompileConfig.h 
        ${PROJECT_SOURCE_DIR}/DxDataType.h 
        ${PROJECT_SOURCE_DIR}/DxDataTypeHTML5.h 
        ${PROJECT_SOURCE_DIR}/DxFunctionHTML5.h 
    DESTINATION 
        ${CMAKE_INSTALL_INCLUDEDIR}
)
