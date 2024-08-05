// -------------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		HTML5用システムプログラム
// 
// 				Ver 3.24b
// 
// -------------------------------------------------------------------------------

// ＤＸライブラリ作成時用定義
#define DX_MAKE

#include "DxWindow.h"
#include "../DxGraphics.h"

#include <emscripten.h>
#include <emscripten/html5.h>

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// プログラム --------------------------------------------------------------------

extern int InitializeWindow( void ) {
    UpdateMainWindowSize();
    return 0;
}

extern void UpdateMainWindowSize() {
    int WindowSizeX ;
	int WindowSizeY ;

	if( GSYS.Screen.Emulation320x240Flag )
    {
        WindowSizeX = 640 ;
        WindowSizeY = 480 ;
    }
    else
    {
        NS_GetDrawScreenSize( &WindowSizeX, &WindowSizeY ) ;
    }

    emscripten_set_canvas_element_size("#canvas", WindowSizeX, WindowSizeY);
}

extern void GetMainWindowSize(int* Width, int* Height) {
	emscripten_get_canvas_element_size("#canvas", Width, Height);
}

#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE