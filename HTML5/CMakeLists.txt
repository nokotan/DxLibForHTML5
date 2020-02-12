cmake_minimum_required(VERSION 3.13)

cmake_policy(SET CMP0076 NEW)



# DxLib

target_sources(DxLib
    PRIVATE
        DxBaseFuncHTML5.cpp
        DxBaseImageHTML5.cpp
        DxFileHTML5.cpp
        DxFontHTML5.cpp
        DxGraphicsFilterHTML5.cpp
        DxGraphicsHTML5.cpp
        DxInputHTML5.cpp
        DxLive2DCubism4HTML5.cpp
        DxLogHTML5.cpp
        DxMaskHTML5.cpp
        DxMemoryHTML5.cpp
        DxModelHTML5.cpp
        DxMovieHTML5.cpp
        DxNetworkHTML5.cpp
        DXShaderCodeBin_Base_HTML5.cpp
        DXShaderCodeBin_Base3D_HTML5.cpp
        DXShaderCodeBin_Filter_HTML5.cpp
        DXShaderCodeBin_Live2D_Cubism4_HTML5.cpp
        DXShaderCodeBin_Model_HTML5.cpp
        DXShaderCodeBin_RgbaMix_HTML5.cpp
        DxSoundConvertHTML5.cpp
        DxSoundHTML5.cpp
        DxSystemHTML5.cpp
        DxThreadHTML5.cpp
)



# DxUseCLib

target_sources(DxUseCLib
    PRIVATE
        DxUseCLibOggHTML5.cpp
)