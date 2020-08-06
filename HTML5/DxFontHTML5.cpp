//-----------------------------------------------------------------------------
// 
// 		ＤＸライブラリ		HTML5用フォント関係プログラム
// 
//  	Ver 3.21f
// 
//-----------------------------------------------------------------------------

// ＤＸライブラリ作成時用定義
#define DX_MAKE

#include "../DxCompileConfig.h"

#ifndef DX_NON_FONT

// インクルード ---------------------------------------------------------------
#include "DxFontHTML5.h"
#include "DxBaseFuncHTML5.h"
#include "DxSystemHTML5.h"
#include "../DxFont.h"
#include "../DxFile.h"
#include "../DxMemory.h"
#include "../DxBaseFunc.h"
#include "../DxSystem.h"
#include "../DxArchive_.h"
#include "../DxLog.h"

#include <math.h>
#include <stdint.h>

#define FT_FLOOR(X) ((X & -64) / 64)
#define FT_CEIL(X)  (((X + 63) & -64) / 64)

/* FIXME: Right now we assume the gray-scale renderer Freetype is using
   supports 256 shades of gray, but we should instead key off of num_grays
   in the result FT_Bitmap after the FT_Render_Glyph() call. */
#define NUM_GRAYS       256

#define DEBUG_FONTS

#ifndef DX_NON_NAMESPACE

namespace DxLib
{

#endif // DX_NON_NAMESPACE

// マクロ定義 -----------------------------------------------------------------

// 構造体宣言 -----------------------------------------------------------------

// データ定義 -----------------------------------------------------------------

FONTSYSTEM_HTML5 FontSystemHTML5 ;

// 関数宣言 -------------------------------------------------------------------

// プログラム -----------------------------------------------------------------

// フォントの HTML5 専用データを解放する
static int TerminateFontHandle_HTML5( FONTMANAGE *ManageData )
{
	FONTMANAGE_PF* font = ManageData->PF;
    
	if ( font->face ) {
		FT_Done_Face( font->face );
	}
	if ( font->args.stream ) {
		DXFREE( font->args.stream );
	}
            
	// 終了
	return 0 ;
}

// InitFontManage の環境依存処理を行う関数
extern int InitFontManage_PF( void )
{
	FT_Error error = FT_Init_FreeType( &FontSystemHTML5.library );
	
	if (error) {
		return -1;
	}

	FontSystemHTML5.initialized = TRUE;
    return 0;
}

// TermFontManage の環境依存処理を行う関数
extern int TermFontManage_PF( void )
{
	FT_Done_FreeType( FontSystemHTML5.library );
	return 0 ;
}

static unsigned long RWread(
    FT_Stream stream,
    unsigned long offset,
    unsigned char* buffer,
    unsigned long count
)
{
    int* src;

    src = (int *)stream->descriptor.pointer;
	FileRead_seek(*src, offset, STREAM_SEEKTYPE_SET);
   
    if ( count == 0 ) {
        return 0;
    }
	
    return FileRead_read(buffer, count, *src);
}

// CreateFontToHandle の環境依存処理を行う関数
extern int CreateFontToHandle_PF( CREATEFONTTOHANDLE_GPARAM *GParam, FONTMANAGE *ManageData, int DefaultCharSet )
{
	// フォントデータファイルを使用する場合は何もせずに終了
	if( ManageData->UseFontDataFile )
	{
		return 0 ;
	}

    FT_Error error;
    FT_Face face;
    FT_Fixed scale;
    
    FT_CharMap found;
    int64_t position = 0;
    int i;
	int ptsize = ManageData->BaseInfo.FontSize;
	FONTMANAGE_PF* font = ManageData->PF;

    if ( ! FontSystemHTML5.initialized ) {
        return -1;
    }

	{
		char UTF8_FontName[ 128 * 4 ] ;	
		int fileHandle ;
		FT_Stream stream ;

		ConvString( ( char * )ManageData->FontName, -1, WCHAR_T_CHARCODEFORMAT, UTF8_FontName, sizeof( UTF8_FontName ), DX_CHARCODEFORMAT_UTF8 ) ;
		stream = (FT_Stream)DXALLOC(sizeof(*stream));

        printf("Font Init: FontName=%s\n", UTF8_FontName);

    	if ( stream == NULL ) {
        	return -1;
		}

		font->src = FileRead_open(UTF8_FontName);

		memset(stream, 0, sizeof(*stream));
    	stream->read = RWread;
    	stream->descriptor.pointer = &font->src;
    	stream->pos = (unsigned long)position;
    	stream->size = (unsigned long)(FileRead_size(UTF8_FontName) - position);

    	font->args.flags = FT_OPEN_STREAM;
    	font->args.stream = stream;

		error = FT_Open_Face( FontSystemHTML5.library, &font->args, 0, &font->face );

		if (error) {
            printf("Font Init Error: FontName=%s, Code=%d\n", UTF8_FontName, error);
			return -1;
		}
    }

	face = font->face;

	{
		/* Set charmap for loaded font */
		found = 0;
		for (i = 0; i < face->num_charmaps; i++) {
			FT_CharMap charmap = face->charmaps[i];
			if ((charmap->platform_id == 3 && charmap->encoding_id == 1) /* Windows Unicode */
			|| (charmap->platform_id == 3 && charmap->encoding_id == 0) /* Windows Symbol */
			|| (charmap->platform_id == 2 && charmap->encoding_id == 1) /* ISO Unicode */
			|| (charmap->platform_id == 0)) { /* Apple Unicode */
				found = charmap;
				break;
			}
		}
		if ( found ) {
			/* If this fails, continue using the default charmap */
			FT_Set_Charmap(face, found);
		}
	}

    /* Make sure that our font face is scalable (global metrics) */
    if ( FT_IS_SCALABLE(face) ) {
        /* Set the character size and use default DPI (72) */
        error = FT_Set_Char_Size( font->face, 0, ptsize * 64, 0, 0 );
        
		if ( error ) {        
            return -1;
        }

        /* Get the scalable font metrics for this font */
        scale = face->size->metrics.y_scale;
		
        font->ascent  = FT_CEIL(FT_MulFix(face->ascender, scale));
        font->descent = FT_CEIL(FT_MulFix(face->descender, scale));
		font->width = FT_CEIL(FT_MulFix(face->bbox.xMax - face->bbox.xMin, scale));
        font->height  = font->ascent - font->descent + /* baseline */ 1;
        font->lineskip = FT_CEIL(FT_MulFix(face->height, scale));
        font->underline_offset = FT_FLOOR(FT_MulFix(face->underline_position, scale));
        font->underline_height = FT_FLOOR(FT_MulFix(face->underline_thickness, scale));

    } else {
        /* Non-scalable font case.  ptsize determines which family
         * or series of fonts to grab from the non-scalable format.
         * It is not the point size of the font.
         * */
        if ( ptsize >= font->face->num_fixed_sizes )
            ptsize = font->face->num_fixed_sizes - 1;
        font->font_size_family = ptsize;
        error = FT_Set_Pixel_Sizes( face,
                face->available_sizes[ptsize].width,
                face->available_sizes[ptsize].height );

        if ( error ) {
            return -1;
        }

        /* With non-scalale fonts, Freetype2 likes to fill many of the
         * font metrics with the value of 0.  The size of the
         * non-scalable fonts must be determined differently
         * or sometimes cannot be determined.
         * */
		font->width = face->available_sizes[ptsize].width;
        font->ascent = face->available_sizes[ptsize].height;
        font->descent = 0;
        font->height = face->available_sizes[ptsize].height;
        font->lineskip = FT_CEIL(font->ascent);
        font->underline_offset = FT_FLOOR(face->underline_position);
        font->underline_height = FT_FLOOR(face->underline_thickness);
    }

    if ( font->underline_height < 1 ) {
        font->underline_height = 1;
    }

#ifdef DEBUG_FONTS
    printf("Font metrics:\n");
    printf("\tascent = %d, descent = %d\n",
        font->ascent, font->descent);
    printf("\theight = %d, lineskip = %d\n",
        font->height, font->lineskip);
    printf("\tunderline_offset = %d, underline_height = %d\n",
        font->underline_offset, font->underline_height);
#endif

    /* Set the default font style */
    font->outline = 0;
    font->kerning = 0;
    font->glyph_overhang = face->size->metrics.y_ppem / 10;
    /* x offset = cos(((90.0-12)/360)*2*M_PI), or 12 degree angle */
    font->glyph_italics = 0.207f;
    font->glyph_italics *= font->height;

    printf("Cache Info: PixelByte=%d, BitWidth=%d\n", ManageData->TextureCacheBaseImage.ColorData.PixelByte, ManageData->TextureCacheBaseImage.ColorData.ColorBitDepth);

	{
		// 成功時はパラメータをセット
		ManageData->BaseInfo.FontHeight    = ManageData->PF->height ;
		ManageData->BaseInfo.FontAddHeight = 0 ;
		ManageData->BaseInfo.MaxWidth      = ManageData->PF->width > ManageData->PF->height ? ManageData->PF->width : ManageData->PF->height;
		ManageData->BaseInfo.Ascent        = -ManageData->PF->ascent;
	}

	// 戻り値を返す
	return 0 ;
}

// CreateFontToHandle の環境依存エラー処理を行う関数
extern int CreateFontToHandle_Error_PF( FONTMANAGE * ManageData )
{
	// 解放処理を実行
	TerminateFontHandle_HTML5( ManageData ) ;

	// 終了
	return 0 ;
}

// TerminateFontHandle の環境依存処理を行う関数
extern int TerminateFontHandle_PF( FONTMANAGE *ManageData )
{
	// 解放処理を実行
	TerminateFontHandle_HTML5( ManageData ) ;

	// 終了
	return 0 ;
}

// SetupFontCache の環境依存処理を行う関数
extern int SetupFontCache_PF( CREATEFONTTOHANDLE_GPARAM * /* GParam */, FONTMANAGE * /* ManageData */, int /* ASyncThread */ )
{
	// 特に何もしない
	return 0 ;
}

// FontCacheCharaAddToHandleの環境依存処理を行う関数( 実行箇所区別 0 )
extern int FontCacheCharAddToHandle_Timing0_PF( FONTMANAGE *ManageData )
{
	// とくにすること無し
	return 0 ;
}

// FontCacheCharaAddToHandleの環境依存処理を行う関数( 実行箇所区別 1 )
extern int FontCacheCharAddToHandle_Timing1_PF( FONTMANAGE *ManageData, FONTCHARDATA *CharData, DWORD CharCode, DWORD IVSCode, int TextureCacheUpdate )
{
	int res = -1 ;
    int Space;

    FT_Face face;
    FT_Error error;
    FT_GlyphSlot glyph;
    FT_Glyph_Metrics* metrics;
    FT_Outline* outline;

	FONTMANAGE_PF* font = ManageData->PF;
	FT_Bitmap bitmap;
	FT_UInt index;

#ifdef DEBUG_FONTS   
    printf("Font Init: Start font caching of %d\n", CharCode);
#endif
	// スペースかどうかを取得しておく
	Space = CharCode == L' ' ? 1 : ( CharCode == ( DWORD )FSYS.DoubleByteSpaceCharCode ? 2 : 0 ) ;

    if ( !font || !font->face ) {
        printf("Font Error: Parameter is NULL!\n");
        return -1;
    }

    face = font->face;

    /* Load the glyph */
    index = FT_Get_Char_Index( face, CharCode );
    
    error = FT_Load_Glyph( face, index, FT_LOAD_DEFAULT | font->hinting);
    if ( error ) {
        printf("Font Error: Glyph cannot loaded! (%d)\n", error);
        return -1;
    }

    /* Get our glyph shortcuts */
    glyph = face->glyph;
    metrics = &glyph->metrics;
    outline = &glyph->outline;
    
	{
        int mono = !(ManageData->FontType & DX_FONTTYPE_ANTIALIASING);
        int i;
        FT_Bitmap* src;
        FT_Bitmap* dst;
        FT_Glyph bitmap_glyph = NULL;

        /* Handle the italic style */
        if ( ManageData->BaseInfo.Italic ) {
            FT_Matrix shear;

            shear.xx = 1 << 16;
            shear.xy = (int) ( font->glyph_italics * ( 1 << 16 ) ) / font->height;
            shear.yx = 0;
            shear.yy = 1 << 16;

            FT_Outline_Transform( outline, &shear );
        }

        /* Render as outline */
        if ( (font->outline > 0) && glyph->format != FT_GLYPH_FORMAT_BITMAP ) {
            FT_Stroker stroker;
            FT_Get_Glyph( glyph, &bitmap_glyph );
            error = FT_Stroker_New( FontSystemHTML5.library, &stroker );
            if ( error ) {
                printf("Font Error: Glyph stroke failed! (%d)\n", error);
                return -1;
            }
            FT_Stroker_Set( stroker, font->outline * 64, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0 );
            FT_Glyph_Stroke( &bitmap_glyph, stroker, 1 /* delete the original glyph */ );
            FT_Stroker_Done( stroker );
            /* Render the glyph */
            error = FT_Glyph_To_Bitmap( &bitmap_glyph, mono ? ft_render_mode_mono : ft_render_mode_normal, 0, 1 );
            if ( error ) {
                printf("Font Error: Glyph convert error to Bitmap! (%d)\n", error);
                FT_Done_Glyph( bitmap_glyph );
                return -1;
            }
            src = &((FT_BitmapGlyph)bitmap_glyph)->bitmap;
        } else {
            /* Render the glyph */
            error = FT_Render_Glyph( glyph, mono ? ft_render_mode_mono : ft_render_mode_normal );
            if ( error ) {
                printf("Font Error: Glyph render failed! (%d)\n", error);
                return -1;
            }
            src = &glyph->bitmap;
        }

        /* Copy over information to cache */
        // if ( mono ) {
        //     dst = &cached->bitmap;
        // } else {
        //     dst = &cached->pixmap;
        // }

        dst = &bitmap;
        memcpy( dst, src, sizeof( *dst ) );

        /* FT_Render_Glyph() and .fon fonts always generate a
         * two-color (black and white) glyphslot surface, even
         * when rendered in ft_render_mode_normal. */
        /* FT_IS_SCALABLE() means that the font is in outline format,
         * but does not imply that outline is rendered as 8-bit
         * grayscale, because embedded bitmap/graymap is preferred
         * (see FT_LOAD_DEFAULT section of FreeType2 API Reference).
         * FT_Render_Glyph() canreturn two-color bitmap or 4/16/256-
         * color graymap according to the format of embedded bitmap/
         * graymap. */
        if ( src->pixel_mode == FT_PIXEL_MODE_MONO ) {
            dst->pitch *= 8;
        } else if ( src->pixel_mode == FT_PIXEL_MODE_GRAY2 ) {
            dst->pitch *= 4;
        } else if ( src->pixel_mode == FT_PIXEL_MODE_GRAY4 ) {
            dst->pitch *= 2;
        }

        /* Adjust for bold and italic text */
        if ( FALSE ) {
            int bump = font->glyph_overhang;
            dst->pitch += bump;
            dst->width += bump;
        }
        if ( ManageData->BaseInfo.Italic ) {
            int bump = (int)ceil(font->glyph_italics);
            dst->pitch += bump;
            dst->width += bump;
        }

        if (dst->rows != 0) {
            dst->buffer = (unsigned char *)DXALLOC( dst->pitch * dst->rows );
            if ( !dst->buffer ) {
                return -1;
            }
            memset( dst->buffer, 0, dst->pitch * dst->rows );

            printf("Font Init: Src Pixel Mode is %d\n", src->pixel_mode);

            for ( i = 0; i < src->rows; i++ ) {
                int soffset = i * src->pitch;
                int doffset = i * dst->pitch;
                if ( mono ) {
                    unsigned char *srcp = src->buffer + soffset;
                    unsigned char *dstp = dst->buffer + doffset;
                    int j;
                    if ( src->pixel_mode == FT_PIXEL_MODE_MONO ) {
                        for ( j = 0; j < src->width; j += 8 ) {
                            unsigned char c = *srcp++;
                            *dstp++ = (c&0x80) >> 7;
                            c <<= 1;
                            *dstp++ = (c&0x80) >> 7;
                            c <<= 1;
                            *dstp++ = (c&0x80) >> 7;
                            c <<= 1;
                            *dstp++ = (c&0x80) >> 7;
                            c <<= 1;
                            *dstp++ = (c&0x80) >> 7;
                            c <<= 1;
                            *dstp++ = (c&0x80) >> 7;
                            c <<= 1;
                            *dstp++ = (c&0x80) >> 7;
                            c <<= 1;
                            *dstp++ = (c&0x80) >> 7;
                        }
                    }  else if ( src->pixel_mode == FT_PIXEL_MODE_GRAY2 ) {
                        for ( j = 0; j < src->width; j += 4 ) {
                            unsigned char c = *srcp++;
                            *dstp++ = (((c&0xC0) >> 6) >= 0x2) ? 1 : 0;
                            c <<= 2;
                            *dstp++ = (((c&0xC0) >> 6) >= 0x2) ? 1 : 0;
                            c <<= 2;
                            *dstp++ = (((c&0xC0) >> 6) >= 0x2) ? 1 : 0;
                            c <<= 2;
                            *dstp++ = (((c&0xC0) >> 6) >= 0x2) ? 1 : 0;
                        }
                    } else if ( src->pixel_mode == FT_PIXEL_MODE_GRAY4 ) {
                        for ( j = 0; j < src->width; j += 2 ) {
                            unsigned char c = *srcp++;
                            *dstp++ = (((c&0xF0) >> 4) >= 0x8) ? 1 : 0;
                            c <<= 4;
                            *dstp++ = (((c&0xF0) >> 4) >= 0x8) ? 1 : 0;
                        }
                    } else {
                        for ( j = 0; j < src->width; j++ ) {
                            unsigned char c = *srcp++;
                            *dstp++ = (c >= 0x80) ? 1 : 0;
                        }
                    }
                } else if ( src->pixel_mode == FT_PIXEL_MODE_MONO ) {
                    /* This special case wouldn't
                     * be here if the FT_Render_Glyph()
                     * function wasn't buggy when it tried
                     * to render a .fon font with 256
                     * shades of gray.  Instead, it
                     * returns a black and white surface
                     * and we have to translate it back
                     * to a 256 gray shaded surface.
                     * */
                    unsigned char *srcp = src->buffer + soffset;
                    unsigned char *dstp = dst->buffer + doffset;
                    unsigned char c;
                    int j, k;
                    for ( j = 0; j < src->width; j += 8) {
                        c = *srcp++;
                        for (k = 0; k < 8; ++k) {
                            if ((c&0x80) >> 7) {
                                *dstp++ = NUM_GRAYS - 1;
                            } else {
                                *dstp++ = 0x00;
                            }
                            c <<= 1;
                        }
                    }
                } else if ( src->pixel_mode == FT_PIXEL_MODE_GRAY2 ) {
                    unsigned char *srcp = src->buffer + soffset;
                    unsigned char *dstp = dst->buffer + doffset;
                    unsigned char c;
                    int j, k;
                    for ( j = 0; j < src->width; j += 4 ) {
                        c = *srcp++;
                        for ( k = 0; k < 4; ++k ) {
                            if ((c&0xC0) >> 6) {
                                *dstp++ = NUM_GRAYS * ((c&0xC0) >> 6) / 3 - 1;
                            } else {
                                *dstp++ = 0x00;
                            }
                            c <<= 2;
                        }
                    }
                } else if ( src->pixel_mode == FT_PIXEL_MODE_GRAY4 ) {
                    unsigned char *srcp = src->buffer + soffset;
                    unsigned char *dstp = dst->buffer + doffset;
                    unsigned char c;
                    int j, k;
                    for ( j = 0; j < src->width; j += 2 ) {
                        c = *srcp++;
                        for ( k = 0; k < 2; ++k ) {
                            if ((c&0xF0) >> 4) {
                                *dstp++ = NUM_GRAYS * ((c&0xF0) >> 4) / 15 - 1;
                            } else {
                                *dstp++ = 0x00;
                            }
                            c <<= 4;
                        }
                    }
                } else {
                    memcpy(dst->buffer+doffset,
                           src->buffer+soffset, src->pitch);
                }
            }
        }

        /* Handle the bold style */
        if ( FALSE ) {
            int row;
            int col;
            int offset;
            int pixel;
            uint8_t* pixmap;

            /* The pixmap is a little hard, we have to add and clamp */
            for ( row = dst->rows - 1; row >= 0; --row ) {
                pixmap = (uint8_t*) dst->buffer + row * dst->pitch;
                for ( offset=1; offset <= font->glyph_overhang; ++offset ) {
                    for ( col = dst->width - 1; col > 0; --col ) {
                        if ( mono ) {
                            pixmap[col] |= pixmap[col-1];
                        } else {
                            pixel = (pixmap[col] + pixmap[col-1]);
                            if ( pixel > NUM_GRAYS - 1 ) {
                                pixel = NUM_GRAYS - 1;
                            }
                            pixmap[col] = (uint8_t) pixel;
                        }
                    }
                }
            }
        }

#ifdef DEBUG_FONTS
        printf("X=%d, Y=%d, Add=%d\n", 
            metrics->horiBearingX / 64,
            font->ascent - metrics->horiBearingY / 64,
            metrics->horiAdvance / 64);
#endif

        if (Space != 0) {
            /* We're done, mark this glyph cached */
            FontCacheCharImageBltToHandle(
                ManageData,
                CharData,
                CharCode,
                IVSCode,
                TRUE,
                mono ? DX_FONT_SRCIMAGETYPE_8BIT_ON_OFF : DX_FONT_SRCIMAGETYPE_8BIT_MAX255,
                NULL,
                0,
                0,
                0,
                0,
                0,
                metrics->horiAdvance / 64, 
                FALSE
            );
        } else {
            /* We're done, mark this glyph cached */
            FontCacheCharImageBltToHandle(
                ManageData,
                CharData,
                CharCode,
                IVSCode,
                FALSE,
                mono ? DX_FONT_SRCIMAGETYPE_8BIT_ON_OFF : DX_FONT_SRCIMAGETYPE_8BIT_MAX255,
                bitmap.buffer,
                bitmap.width,
                bitmap.rows,
                bitmap.pitch,
                metrics->horiBearingX / 64,
                font->ascent - metrics->horiBearingY / 64,
                metrics->horiAdvance / 64, 
                TextureCacheUpdate
            );
        }

        /* Free outlined glyph */
        if ( bitmap_glyph ) {
            FT_Done_Glyph( bitmap_glyph );
        }
    }

	DXFREE(bitmap.buffer);
	res = 0;

	// 戻り値を返す
	return res ;
}

// FontCacheCharaAddToHandleの環境依存処理を行う関数( 実行箇所区別 2 )
extern int FontCacheCharAddToHandle_Timing2_PF( FONTMANAGE *ManageData )
{
	// 特に何もしない
	return 0 ;
}

// EnumFontName の環境依存処理を行う関数
extern int EnumFontName_PF( ENUMFONTDATA *EnumFontData, int IsEx, int CharSet )
{
	// 正常終了
	return 0 ;
}



#ifndef DX_NON_NAMESPACE

}

#endif // DX_NON_NAMESPACE


#endif // DX_NON_FONT

