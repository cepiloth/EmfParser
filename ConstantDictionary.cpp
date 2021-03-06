/***************************************************************************
* Copyright (C) 2017, Deping Chen, cdp97531@sina.com
*
* All rights reserved.
* For permission requests, write to the author.
*
* This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
* KIND, either express or implied.
***************************************************************************/
#include <Windows.h>
#include "ConstantDictionary.h"

#define CASE(name)		\
	case name:			\
		str = #name;	\
		break;

#define OrSymbol(name)			\
if (mode & name)				\
{								\
	if (cur != g_symbolsBuffer)	\
	{							\
		strcpy(cur, g_or);		\
		cur += g_orLen;			\
	}							\
	strcpy(cur, #name);			\
	cur += strlen(cur);			\
}

#define EndOrSymbol(mask)		\
mode &= ~mask;					\
if (mode)						\
{								\
	if (cur != g_symbolsBuffer)	\
	{							\
		strcpy(cur, g_or);		\
		cur += g_orLen;			\
	}							\
	itoa(mode, cur, 10);		\
}


ConstantDictionary::ConstantDictionary()
{
}


ConstantDictionary::~ConstantDictionary()
{
}

const char g_or[] = " | ";
size_t g_orLen = sizeof(g_or) - 1;
// Not thread safe! But no problem in this program.
char g_intBuffer[12];
char g_symbolsBuffer[256];
const char * ConstantDictionary::BkMode(int mode)
{
	g_intBuffer[0] = '\0';
	const char* str;
	switch (mode)
	{
	CASE(TRANSPARENT)
	CASE(OPAQUE)
	default:
		str = itoa(mode, g_intBuffer, 10);
		break;
	}
	return str;
}

const char * ConstantDictionary::BigBool(int mode)
{
	const char* str;
	if (mode)
	{
		str = "TRUE";
	}
	else
	{
		str = "FALSE";
	}
	return str;
}

const char * ConstantDictionary::BrushStyle(int mode)
{
	g_intBuffer[0] = '\0';
	const char* str;
	switch (mode)
	{
	CASE(BS_SOLID)
	CASE(BS_NULL)
	CASE(BS_HATCHED)
	CASE(BS_PATTERN)
	CASE(BS_INDEXED)
	CASE(BS_DIBPATTERN)
	CASE(BS_DIBPATTERNPT)
	CASE(BS_PATTERN8X8)
	CASE(BS_DIBPATTERN8X8)
	CASE(BS_MONOPATTERN)
	default:
		str = itoa(mode, g_intBuffer, 10);
		break;
	}
	return str;
}

const char * ConstantDictionary::CharSet(int mode)
{
	g_intBuffer[0] = '\0';
	const char* str;
	switch (mode)
	{
	CASE(ANSI_CHARSET)
	CASE(DEFAULT_CHARSET)
	CASE(SYMBOL_CHARSET)
	CASE(SHIFTJIS_CHARSET)
	CASE(HANGEUL_CHARSET)
	CASE(GB2312_CHARSET)
	CASE(CHINESEBIG5_CHARSET)
	CASE(OEM_CHARSET)
#if(WINVER >= 0x0400)
	CASE(JOHAB_CHARSET)
	CASE(HEBREW_CHARSET)
	CASE(ARABIC_CHARSET)
	CASE(GREEK_CHARSET)
	CASE(TURKISH_CHARSET)
	CASE(VIETNAMESE_CHARSET)
	CASE(THAI_CHARSET)
	CASE(EASTEUROPE_CHARSET)
	CASE(RUSSIAN_CHARSET)

	CASE(MAC_CHARSET)
	CASE(BALTIC_CHARSET)
#endif
	default:
		str = itoa(mode, g_intBuffer, 10);
		break;
	}
	return str;
}

const char * ConstantDictionary::CharPrecision(int mode)
{
	g_intBuffer[0] = '\0';
	const char* str;
	switch (mode)
	{
	CASE(OUT_DEFAULT_PRECIS)
	CASE(OUT_STRING_PRECIS)
	CASE(OUT_CHARACTER_PRECIS)
	CASE(OUT_STROKE_PRECIS)
	CASE(OUT_TT_PRECIS)
	CASE(OUT_DEVICE_PRECIS)
	CASE(OUT_RASTER_PRECIS)
	CASE(OUT_TT_ONLY_PRECIS)
	CASE(OUT_OUTLINE_PRECIS)
	CASE(OUT_SCREEN_OUTLINE_PRECIS)
	CASE(OUT_PS_ONLY_PRECIS)
	default:
		str = itoa(mode, g_intBuffer, 10);
		break;
	}
	return str;
}

const char * ConstantDictionary::CharQuality(int mode)
{
	g_intBuffer[0] = '\0';
	const char* str;
	switch (mode)
	{
	CASE(DEFAULT_QUALITY)
	CASE(DRAFT_QUALITY)
	CASE(PROOF_QUALITY)
#if(WINVER >= 0x0400)
	CASE(NONANTIALIASED_QUALITY)
	CASE(ANTIALIASED_QUALITY)
#endif /* WINVER >= 0x0400 */
	default:
		str = itoa(mode, g_intBuffer, 10);
		break;
	}
	return str;
}

const char * ConstantDictionary::ClipPrecision(int mode)
{
	if (mode == 0)
	{
		return "CLIP_DEFAULT_PRECIS";
	}

	g_symbolsBuffer[0] = '\0';
	char* cur;
	cur = g_symbolsBuffer;

	OrSymbol(CLIP_CHARACTER_PRECIS)
	OrSymbol(CLIP_STROKE_PRECIS)
	OrSymbol(CLIP_LH_ANGLES)
	OrSymbol(CLIP_TT_ALWAYS)
#if (_WIN32_WINNT >= _WIN32_WINNT_LONGHORN)
	OrSymbol(CLIP_DFA_DISABLE)
#endif // (_WIN32_WINNT >= _WIN32_WINNT_LONGHORN)
	OrSymbol(CLIP_EMBEDDED)

	return g_symbolsBuffer;
}

const char * ConstantDictionary::ClipRgnMergeMode(int mode)
{
	g_intBuffer[0] = '\0';
	const char* str;
	switch (mode)
	{
	CASE(RGN_AND)
	CASE(RGN_OR)
	CASE(RGN_XOR)
	CASE(RGN_DIFF)
	default:
		str = itoa(mode, g_intBuffer, 10);
		break;
	}
	return str;
}

const char * ConstantDictionary::ColorTableUsage(int mode)
{
	g_intBuffer[0] = '\0';
	const char* str;
	switch (mode)
	{
	CASE(DIB_RGB_COLORS)
	CASE(DIB_PAL_COLORS)
	default:
		str = itoa(mode, g_intBuffer, 10);
		break;
	}
	return str;
}

const char * ConstantDictionary::ExtTextOutOptions(int mode)
{
	if (mode == 0)
	{
		g_symbolsBuffer[0] = '0';
		g_symbolsBuffer[1] = '\0';
		return g_symbolsBuffer;
	}

	g_symbolsBuffer[0] = '\0';
	char* cur;
	cur = g_symbolsBuffer;

	OrSymbol(ETO_OPAQUE);
	OrSymbol(ETO_CLIPPED);
#if(WINVER >= 0x0400)
	OrSymbol(ETO_GLYPH_INDEX);
	OrSymbol(ETO_RTLREADING);
	OrSymbol(ETO_NUMERICSLOCAL);
	OrSymbol(ETO_NUMERICSLATIN);
	OrSymbol(ETO_IGNORELANGUAGE);
#endif /* WINVER >= 0x0400 */
#if (_WIN32_WINNT >= _WIN32_WINNT_WIN2K)
	OrSymbol(ETO_PDY);
#endif // (_WIN32_WINNT >= _WIN32_WINNT_WIN2K)
#if (_WIN32_WINNT >= _WIN32_WINNT_LONGHORN)
	OrSymbol(ETO_REVERSE_INDEX_MAP);
#endif

	EndOrSymbol(0x1FFFF);

	return g_symbolsBuffer;
}

const char * ConstantDictionary::FontWeight(int mode)
{
	g_intBuffer[0] = '\0';
	const char* str;
	switch (mode)
	{
	CASE(FW_DONTCARE)
	CASE(FW_THIN)
	CASE(FW_EXTRALIGHT)
	CASE(FW_LIGHT)
	CASE(FW_NORMAL)
	CASE(FW_MEDIUM)
	CASE(FW_SEMIBOLD)
	CASE(FW_BOLD)
	CASE(FW_EXTRABOLD)
	CASE(FW_HEAVY)
	default:
		str = itoa(mode, g_intBuffer, 10);
		break;
	}
	return str;
}

const char * ConstantDictionary::HatchStyle(int mode)
{
	g_intBuffer[0] = '\0';
	const char* str;
	switch (mode)
	{
	CASE(HS_HORIZONTAL)
	CASE(HS_VERTICAL)
	CASE(HS_FDIAGONAL)
	CASE(HS_BDIAGONAL)
	CASE(HS_CROSS)
	CASE(HS_DIAGCROSS)
	default:
		str = itoa(mode, g_intBuffer, 10);
		break;
	}
	return str;
}

const char * ConstantDictionary::ICMMode(int mode)
{
	g_intBuffer[0] = '\0';
	const char* str;
	switch (mode)
	{
	CASE(ICM_OFF)
	CASE(ICM_ON)
	CASE(ICM_QUERY)
	CASE(ICM_DONE_OUTSIDEDC)
	default:
		str = itoa(mode, g_intBuffer, 10);
		break;
	}
	return str;
}

const char * ConstantDictionary::Layout(int mode)
{
	if (mode == 0)
	{
		g_symbolsBuffer[0] = '0';
		g_symbolsBuffer[1] = '\0';
		return g_symbolsBuffer;
	}

	g_symbolsBuffer[0] = '\0';
	char* cur;
	cur = g_symbolsBuffer;

	OrSymbol(LAYOUT_RTL);
	OrSymbol(LAYOUT_BTT);
	OrSymbol(LAYOUT_VBH);
	OrSymbol(LAYOUT_BITMAPORIENTATIONPRESERVED);

	EndOrSymbol(0xF);

	return g_symbolsBuffer;
}

const char * ConstantDictionary::MapMode(int mode)
{
	g_intBuffer[0] = '\0';
	const char* str;
	switch (mode)
	{
	CASE(MM_TEXT)
	CASE(MM_LOMETRIC)
	CASE(MM_HIMETRIC)
	CASE(MM_LOENGLISH)
	CASE(MM_HIENGLISH)
	CASE(MM_TWIPS)
	CASE(MM_ISOTROPIC)
	CASE(MM_ANISOTROPIC)
	default:
		str = itoa(mode, g_intBuffer, 10);
		break;
	}
	return str;
}

const char * ConstantDictionary::PenStyle(int mode)
{
	g_symbolsBuffer[0] = '\0';
	char* cur;
	cur = g_symbolsBuffer;

	const char* str;

	g_intBuffer[0] = '\0';
	switch (mode & PS_STYLE_MASK)
	{
	CASE(PS_SOLID)
	CASE(PS_DASH)
	CASE(PS_DOT)
	CASE(PS_DASHDOT)
	CASE(PS_DASHDOTDOT)
	CASE(PS_NULL)
	CASE(PS_INSIDEFRAME)
	CASE(PS_USERSTYLE)
	CASE(PS_ALTERNATE)
	default:
		str = itoa(mode & PS_STYLE_MASK, g_intBuffer, 10);
		break;
	}
	strcpy(cur, str);
	cur += strlen(cur);

	strcpy(cur, g_or);
	cur += g_orLen;
	g_intBuffer[0] = '\0';
	switch (mode & PS_ENDCAP_MASK)
	{
	CASE(PS_ENDCAP_ROUND)
	CASE(PS_ENDCAP_SQUARE)
	CASE(PS_ENDCAP_FLAT)
	default:
		str = itoa(mode & PS_ENDCAP_MASK, g_intBuffer, 10);
		break;
	}
	strcpy(cur, str);
	cur += strlen(cur);

	strcpy(cur, g_or);
	cur += g_orLen;
	g_intBuffer[0] = '\0';
	switch (mode & PS_JOIN_MASK)
	{
	CASE(PS_JOIN_ROUND)
	CASE(PS_JOIN_BEVEL)
	CASE(PS_JOIN_MITER)
	default:
		str = itoa(mode & PS_JOIN_MASK, g_intBuffer, 10);
		break;
	}
	strcpy(cur, str);
	cur += strlen(cur);

	strcpy(cur, g_or);
	cur += g_orLen;
	g_intBuffer[0] = '\0';
	switch (mode & PS_TYPE_MASK)
	{
	CASE(PS_COSMETIC)
	CASE(PS_GEOMETRIC)
	default:
		str = itoa(mode & PS_TYPE_MASK, g_intBuffer, 10);
		break;
	}
	strcpy(cur, str);
	cur += strlen(cur);

	return g_symbolsBuffer;
}

const char * ConstantDictionary::PitchAndFamily(int mode)
{
	g_symbolsBuffer[0] = '\0';
	char* cur;
	cur = g_symbolsBuffer;

	g_intBuffer[0] = '\0';
	const char* str;
	switch (mode & 0xF)
	{
	CASE(DEFAULT_PITCH)
	CASE(FIXED_PITCH)
	CASE(VARIABLE_PITCH)
#if(WINVER >= 0x0400)
	CASE(MONO_FONT)
#endif /* WINVER >= 0x0400 */
	default:
		str = itoa(mode, g_intBuffer, 10);
		break;
	}
	strcpy(cur, str);
	cur += strlen(cur);

	strcpy(cur, g_or);
	cur += g_orLen;

	switch (mode & ~0xF)
	{
	CASE(FF_DONTCARE)
	CASE(FF_ROMAN)
	CASE(FF_SWISS)
	CASE(FF_MODERN)
	CASE(FF_SCRIPT)
	CASE(FF_DECORATIVE)
	default:
		str = itoa(mode, g_intBuffer, 10);
		break;
	}
	strcpy(cur, str);
	cur += strlen(cur);

	return g_symbolsBuffer;
}

const char * ConstantDictionary::PolyFillMode(int mode)
{
	g_intBuffer[0] = '\0';
	const char* str;
	switch (mode)
	{
	CASE(ALTERNATE)
	CASE(WINDING)
	default:
		str = itoa(mode, g_intBuffer, 10);
		break;
	}
	return str;
}

const char * ConstantDictionary::RGBColor(int rgb)
{
	g_symbolsBuffer[0] = '\0';
	char* cur = g_symbolsBuffer;

	strcpy(cur, "RGB(");
	cur += strlen(cur);
	itoa(GetRValue(rgb), cur, 10);
	cur += strlen(cur);
	strcpy(cur, ",");
	cur += strlen(cur);
	itoa(GetGValue(rgb), cur, 10);
	cur += strlen(cur);
	strcpy(cur, ",");
	cur += strlen(cur);
	itoa(GetBValue(rgb), cur, 10);
	cur += strlen(cur);
	strcpy(cur, ")");
	return g_symbolsBuffer;
}

const char * ConstantDictionary::ROP2(int mode)
{
	g_intBuffer[0] = '\0';
	const char* str;
	switch (mode)
	{
	CASE(R2_BLACK)
	CASE(R2_NOTMERGEPEN)
	CASE(R2_MASKNOTPEN)
	CASE(R2_NOTCOPYPEN)
	CASE(R2_MASKPENNOT)
	CASE(R2_NOT)
	CASE(R2_XORPEN)
	CASE(R2_NOTMASKPEN)
	CASE(R2_MASKPEN)
	CASE(R2_NOTXORPEN)
	CASE(R2_NOP)
	CASE(R2_MERGENOTPEN)
	CASE(R2_COPYPEN)
	CASE(R2_MERGEPENNOT)
	CASE(R2_MERGEPEN)
	CASE(R2_WHITE)
	default:
		str = itoa(mode, g_intBuffer, 10);
		break;
	}
	return str;
}

const char * ConstantDictionary::ROP3(int mode)
{
	g_intBuffer[0] = '\0';
	const char* str;
	switch (mode)
	{
	CASE(SRCCOPY)
	CASE(SRCPAINT)
	CASE(SRCAND)
	CASE(SRCINVERT)
	CASE(SRCERASE)
	CASE(NOTSRCCOPY)
	CASE(NOTSRCERASE)
	CASE(MERGECOPY)
	CASE(MERGEPAINT)
	CASE(PATCOPY)
	CASE(PATPAINT)
	CASE(PATINVERT)
	CASE(DSTINVERT)
	CASE(BLACKNESS)
	CASE(WHITENESS)
	default:
		str = itoa(mode, g_intBuffer, 10);
		break;
	}
	return str;
}

const char * ConstantDictionary::StockObject(int name)
{
	g_intBuffer[0] = '\0';
	const char* str;
	switch (name)
	{
	CASE(WHITE_BRUSH)
	CASE(LTGRAY_BRUSH)
	CASE(GRAY_BRUSH)
	CASE(DKGRAY_BRUSH)
	CASE(BLACK_BRUSH)
	CASE(NULL_BRUSH)
	CASE(WHITE_PEN)
	CASE(BLACK_PEN)
	CASE(NULL_PEN)
	CASE(OEM_FIXED_FONT)
	CASE(ANSI_FIXED_FONT)
	CASE(ANSI_VAR_FONT)
	CASE(SYSTEM_FONT)
	CASE(DEVICE_DEFAULT_FONT)
	CASE(DEFAULT_PALETTE)
	CASE(SYSTEM_FIXED_FONT)
	CASE(DEFAULT_GUI_FONT)
	CASE(DC_BRUSH)
	CASE(DC_PEN)
	default:
		str = itoa(name, g_intBuffer, 10);
		break;
	}
	return str;
}

const char * ConstantDictionary::StretchBltMode(int mode)
{
	g_intBuffer[0] = '\0';
	const char* str;
	switch (mode)
	{
	CASE(BLACKONWHITE)
	CASE(WHITEONBLACK)
	CASE(COLORONCOLOR)
	CASE(HALFTONE)
	default:
		str = itoa(mode, g_intBuffer, 10);
		break;
	}
	return str;
}

const char * ConstantDictionary::TextAlign(int mode)
{
	//#define TA_NOUPDATECP                0
	//#define TA_UPDATECP                  1
	//
	//#define TA_LEFT                      0
	//#define TA_RIGHT                     2
	//#define TA_CENTER                    6
	//
	//#define TA_TOP                       0
	//#define TA_BOTTOM                    8
	//#define TA_BASELINE                  24
	//#if (WINVER >= 0x0400)
	//#define TA_RTLREADING                256
	//#define TA_MASK       (TA_BASELINE+TA_CENTER+TA_UPDATECP+TA_RTLREADING)
	//#else
	//#define TA_MASK       (TA_BASELINE+TA_CENTER+TA_UPDATECP)
	//#endif
	g_symbolsBuffer[0] = '\0';
	char* cur;

	if ((mode & ~TA_MASK) != 0 || (mode & TA_CENTER) == 4 || (mode & TA_BASELINE) == 16)
	{
		itoa(mode, g_symbolsBuffer, 10);
	}
	else
	{
		cur = g_symbolsBuffer;

		if (mode & TA_UPDATECP)
		{
			strcpy(cur, "TA_UPDATECP");
		}
		cur += strlen(cur);

		if (mode & TA_CENTER)
		{
			if (cur == g_symbolsBuffer)
				strcpy(cur, "TA_CENTER");
			else
				strcpy(cur, " | TA_CENTER");
		}
		else if (mode & TA_RIGHT)
		{
			if (cur == g_symbolsBuffer)
				strcpy(cur, "TA_RIGHT");
			else
				strcpy(cur, " | TA_RIGHT");
		}
		else
		{
			if (cur == g_symbolsBuffer)
				strcpy(cur, "TA_LEFT");
			else
				strcpy(cur, " | TA_LEFT");
		}
		cur += strlen(cur);

		if (mode & TA_BASELINE)
		{
			strcpy(cur, " | TA_BASELINE");
		}
		else if (mode & TA_BOTTOM)
		{
			strcpy(cur, " | TA_BOTTOM");
		}
		else
		{
			strcpy(cur, " | TA_TOP");
		}
		cur += strlen(cur);

		if (mode & TA_RTLREADING)
		{
			strcpy(cur, " | TA_RTLREADING");
		}
	}
	return g_symbolsBuffer;
}

const char * ConstantDictionary::WorldTransform(int mode)
{
	g_intBuffer[0] = '\0';
	const char* str;
	switch (mode)
	{
	CASE(MWT_IDENTITY)
	CASE(MWT_LEFTMULTIPLY)
	CASE(MWT_RIGHTMULTIPLY)
	default:
		str = itoa(mode, g_intBuffer, 10);
		break;
	}
	return str;
}

#include <GdiplusEnums.h>
const char * ConstantDictionary::EmfPlusRecordType(int type)
{
	g_intBuffer[0] = '\0';
	const char* str;
	switch (type)
	{
	CASE(WmfRecordTypeSetBkMode)
	CASE(WmfRecordTypeSetMapMode)
	CASE(WmfRecordTypeSetROP2)
	CASE(WmfRecordTypeSetRelAbs)
	CASE(WmfRecordTypeSetPolyFillMode)
	CASE(WmfRecordTypeSetStretchBltMode)
	CASE(WmfRecordTypeSetTextCharExtra)
	CASE(WmfRecordTypeSetTextColor)
	CASE(WmfRecordTypeSetTextJustification)
	CASE(WmfRecordTypeSetWindowOrg)
	CASE(WmfRecordTypeSetWindowExt)
	CASE(WmfRecordTypeSetViewportOrg)
	CASE(WmfRecordTypeSetViewportExt)
	CASE(WmfRecordTypeOffsetWindowOrg)
	CASE(WmfRecordTypeScaleWindowExt)
	CASE(WmfRecordTypeOffsetViewportOrg)
	CASE(WmfRecordTypeScaleViewportExt)
	CASE(WmfRecordTypeLineTo)
	CASE(WmfRecordTypeMoveTo)
	CASE(WmfRecordTypeExcludeClipRect)
	CASE(WmfRecordTypeIntersectClipRect)
	CASE(WmfRecordTypeArc)
	CASE(WmfRecordTypeEllipse)
	CASE(WmfRecordTypeFloodFill)
	CASE(WmfRecordTypePie)
	CASE(WmfRecordTypeRectangle)
	CASE(WmfRecordTypeRoundRect)
	CASE(WmfRecordTypePatBlt)
	CASE(WmfRecordTypeSaveDC)
	CASE(WmfRecordTypeSetPixel)
	CASE(WmfRecordTypeOffsetClipRgn)
	CASE(WmfRecordTypeTextOut)
	CASE(WmfRecordTypeBitBlt)
	CASE(WmfRecordTypeStretchBlt)
	CASE(WmfRecordTypePolygon)
	CASE(WmfRecordTypePolyline)
	CASE(WmfRecordTypeEscape)
	CASE(WmfRecordTypeRestoreDC)
	CASE(WmfRecordTypeFillRegion)
	CASE(WmfRecordTypeFrameRegion)
	CASE(WmfRecordTypeInvertRegion)
	CASE(WmfRecordTypePaintRegion)
	CASE(WmfRecordTypeSelectClipRegion)
	CASE(WmfRecordTypeSelectObject)
	CASE(WmfRecordTypeSetTextAlign)
	CASE(WmfRecordTypeDrawText)
	CASE(WmfRecordTypeChord)
	CASE(WmfRecordTypeSetMapperFlags)
	CASE(WmfRecordTypeExtTextOut)
	CASE(WmfRecordTypeSetDIBToDev)
	CASE(WmfRecordTypeSelectPalette)
	CASE(WmfRecordTypeRealizePalette)
	CASE(WmfRecordTypeAnimatePalette)
	CASE(WmfRecordTypeSetPalEntries)
	CASE(WmfRecordTypePolyPolygon)
	CASE(WmfRecordTypeResizePalette)
	CASE(WmfRecordTypeDIBBitBlt)
	CASE(WmfRecordTypeDIBStretchBlt)
	CASE(WmfRecordTypeDIBCreatePatternBrush)
	CASE(WmfRecordTypeStretchDIB)
	CASE(WmfRecordTypeExtFloodFill)
	CASE(WmfRecordTypeSetLayout)
	CASE(WmfRecordTypeResetDC)
	CASE(WmfRecordTypeStartDoc)
	CASE(WmfRecordTypeStartPage)
	CASE(WmfRecordTypeEndPage)
	CASE(WmfRecordTypeAbortDoc)
	CASE(WmfRecordTypeEndDoc)
	CASE(WmfRecordTypeDeleteObject)
	CASE(WmfRecordTypeCreatePalette)
	CASE(WmfRecordTypeCreateBrush)
	CASE(WmfRecordTypeCreatePatternBrush)
	CASE(WmfRecordTypeCreatePenIndirect)
	CASE(WmfRecordTypeCreateFontIndirect)
	CASE(WmfRecordTypeCreateBrushIndirect)
	CASE(WmfRecordTypeCreateBitmapIndirect)
	CASE(WmfRecordTypeCreateBitmap)
	CASE(WmfRecordTypeCreateRegion)
	CASE(EmfRecordTypeHeader)
	CASE(EmfRecordTypePolyBezier)
	CASE(EmfRecordTypePolygon)
	CASE(EmfRecordTypePolyline)
	CASE(EmfRecordTypePolyBezierTo)
	CASE(EmfRecordTypePolyLineTo)
	CASE(EmfRecordTypePolyPolyline)
	CASE(EmfRecordTypePolyPolygon)
	CASE(EmfRecordTypeSetWindowExtEx)
	CASE(EmfRecordTypeSetWindowOrgEx)
	CASE(EmfRecordTypeSetViewportExtEx)
	CASE(EmfRecordTypeSetViewportOrgEx)
	CASE(EmfRecordTypeSetBrushOrgEx)
	CASE(EmfRecordTypeEOF)
	CASE(EmfRecordTypeSetPixelV)
	CASE(EmfRecordTypeSetMapperFlags)
	CASE(EmfRecordTypeSetMapMode)
	CASE(EmfRecordTypeSetBkMode)
	CASE(EmfRecordTypeSetPolyFillMode)
	CASE(EmfRecordTypeSetROP2)
	CASE(EmfRecordTypeSetStretchBltMode)
	CASE(EmfRecordTypeSetTextAlign)
	CASE(EmfRecordTypeSetColorAdjustment)
	CASE(EmfRecordTypeSetTextColor)
	CASE(EmfRecordTypeSetBkColor)
	CASE(EmfRecordTypeOffsetClipRgn)
	CASE(EmfRecordTypeMoveToEx)
	CASE(EmfRecordTypeSetMetaRgn)
	CASE(EmfRecordTypeExcludeClipRect)
	CASE(EmfRecordTypeIntersectClipRect)
	CASE(EmfRecordTypeScaleViewportExtEx)
	CASE(EmfRecordTypeScaleWindowExtEx)
	CASE(EmfRecordTypeSaveDC)
	CASE(EmfRecordTypeRestoreDC)
	CASE(EmfRecordTypeSetWorldTransform)
	CASE(EmfRecordTypeModifyWorldTransform)
	CASE(EmfRecordTypeSelectObject)
	CASE(EmfRecordTypeCreatePen)
	CASE(EmfRecordTypeCreateBrushIndirect)
	CASE(EmfRecordTypeDeleteObject)
	CASE(EmfRecordTypeAngleArc)
	CASE(EmfRecordTypeEllipse)
	CASE(EmfRecordTypeRectangle)
	CASE(EmfRecordTypeRoundRect)
	CASE(EmfRecordTypeArc)
	CASE(EmfRecordTypeChord)
	CASE(EmfRecordTypePie)
	CASE(EmfRecordTypeSelectPalette)
	CASE(EmfRecordTypeCreatePalette)
	CASE(EmfRecordTypeSetPaletteEntries)
	CASE(EmfRecordTypeResizePalette)
	CASE(EmfRecordTypeRealizePalette)
	CASE(EmfRecordTypeExtFloodFill)
	CASE(EmfRecordTypeLineTo)
	CASE(EmfRecordTypeArcTo)
	CASE(EmfRecordTypePolyDraw)
	CASE(EmfRecordTypeSetArcDirection)
	CASE(EmfRecordTypeSetMiterLimit)
	CASE(EmfRecordTypeBeginPath)
	CASE(EmfRecordTypeEndPath)
	CASE(EmfRecordTypeCloseFigure)
	CASE(EmfRecordTypeFillPath)
	CASE(EmfRecordTypeStrokeAndFillPath)
	CASE(EmfRecordTypeStrokePath)
	CASE(EmfRecordTypeFlattenPath)
	CASE(EmfRecordTypeWidenPath)
	CASE(EmfRecordTypeSelectClipPath)
	CASE(EmfRecordTypeAbortPath)
	CASE(EmfRecordTypeReserved_069)
	CASE(EmfRecordTypeGdiComment)
	CASE(EmfRecordTypeFillRgn)
	CASE(EmfRecordTypeFrameRgn)
	CASE(EmfRecordTypeInvertRgn)
	CASE(EmfRecordTypePaintRgn)
	CASE(EmfRecordTypeExtSelectClipRgn)
	CASE(EmfRecordTypeBitBlt)
	CASE(EmfRecordTypeStretchBlt)
	CASE(EmfRecordTypeMaskBlt)
	CASE(EmfRecordTypePlgBlt)
	CASE(EmfRecordTypeSetDIBitsToDevice)
	CASE(EmfRecordTypeStretchDIBits)
	CASE(EmfRecordTypeExtCreateFontIndirect)
	CASE(EmfRecordTypeExtTextOutA)
	CASE(EmfRecordTypeExtTextOutW)
	CASE(EmfRecordTypePolyBezier16)
	CASE(EmfRecordTypePolygon16)
	CASE(EmfRecordTypePolyline16)
	CASE(EmfRecordTypePolyBezierTo16)
	CASE(EmfRecordTypePolylineTo16)
	CASE(EmfRecordTypePolyPolyline16)
	CASE(EmfRecordTypePolyPolygon16)
	CASE(EmfRecordTypePolyDraw16)
	CASE(EmfRecordTypeCreateMonoBrush)
	CASE(EmfRecordTypeCreateDIBPatternBrushPt)
	CASE(EmfRecordTypeExtCreatePen)
	CASE(EmfRecordTypePolyTextOutA)
	CASE(EmfRecordTypePolyTextOutW)
	CASE(EmfRecordTypeSetICMMode)
	CASE(EmfRecordTypeCreateColorSpace)
	CASE(EmfRecordTypeSetColorSpace)
	CASE(EmfRecordTypeDeleteColorSpace)
	CASE(EmfRecordTypeGLSRecord)
	CASE(EmfRecordTypeGLSBoundedRecord)
	CASE(EmfRecordTypePixelFormat)
	CASE(EmfRecordTypeDrawEscape)
	CASE(EmfRecordTypeExtEscape)
	CASE(EmfRecordTypeStartDoc)
	CASE(EmfRecordTypeSmallTextOut)
	CASE(EmfRecordTypeForceUFIMapping)
	CASE(EmfRecordTypeNamedEscape)
	CASE(EmfRecordTypeColorCorrectPalette)
	CASE(EmfRecordTypeSetICMProfileA)
	CASE(EmfRecordTypeSetICMProfileW)
	CASE(EmfRecordTypeAlphaBlend)
	CASE(EmfRecordTypeSetLayout)
	CASE(EmfRecordTypeTransparentBlt)
	CASE(EmfRecordTypeReserved_117)
	CASE(EmfRecordTypeGradientFill)
	CASE(EmfRecordTypeSetLinkedUFIs)
	CASE(EmfRecordTypeSetTextJustification)
	CASE(EmfRecordTypeColorMatchToTargetW)
	CASE(EmfRecordTypeCreateColorSpaceW)
		// That is the END of the GDI EMF records.

		// Now we start the list of EMF+ records.  We leave quite
		// a bit of room here for the addition of any new GDI
		// records that may be added later.
	CASE(EmfPlusRecordTypeInvalid)
	CASE(EmfPlusRecordTypeHeader)
	CASE(EmfPlusRecordTypeEndOfFile)
	CASE(EmfPlusRecordTypeComment)
	CASE(EmfPlusRecordTypeGetDC)
	CASE(EmfPlusRecordTypeMultiFormatStart)
	CASE(EmfPlusRecordTypeMultiFormatSection)
	CASE(EmfPlusRecordTypeMultiFormatEnd)

		// For all persistent objects
	CASE(EmfPlusRecordTypeObject)

		// Drawing Records
	CASE(EmfPlusRecordTypeClear)
	CASE(EmfPlusRecordTypeFillRects)
	CASE(EmfPlusRecordTypeDrawRects)
	CASE(EmfPlusRecordTypeFillPolygon)
	CASE(EmfPlusRecordTypeDrawLines)
	CASE(EmfPlusRecordTypeFillEllipse)
	CASE(EmfPlusRecordTypeDrawEllipse)
	CASE(EmfPlusRecordTypeFillPie)
	CASE(EmfPlusRecordTypeDrawPie)
	CASE(EmfPlusRecordTypeDrawArc)
	CASE(EmfPlusRecordTypeFillRegion)
	CASE(EmfPlusRecordTypeFillPath)
	CASE(EmfPlusRecordTypeDrawPath)
	CASE(EmfPlusRecordTypeFillClosedCurve)
	CASE(EmfPlusRecordTypeDrawClosedCurve)
	CASE(EmfPlusRecordTypeDrawCurve)
	CASE(EmfPlusRecordTypeDrawBeziers)
	CASE(EmfPlusRecordTypeDrawImage)
	CASE(EmfPlusRecordTypeDrawImagePoints)
	CASE(EmfPlusRecordTypeDrawString)

		// Graphics State Records
	CASE(EmfPlusRecordTypeSetRenderingOrigin)
	CASE(EmfPlusRecordTypeSetAntiAliasMode)
	CASE(EmfPlusRecordTypeSetTextRenderingHint)
	CASE(EmfPlusRecordTypeSetTextContrast)
	CASE(EmfPlusRecordTypeSetInterpolationMode)
	CASE(EmfPlusRecordTypeSetPixelOffsetMode)
	CASE(EmfPlusRecordTypeSetCompositingMode)
	CASE(EmfPlusRecordTypeSetCompositingQuality)
	CASE(EmfPlusRecordTypeSave)
	CASE(EmfPlusRecordTypeRestore)
	CASE(EmfPlusRecordTypeBeginContainer)
	CASE(EmfPlusRecordTypeBeginContainerNoParams)
	CASE(EmfPlusRecordTypeEndContainer)
	CASE(EmfPlusRecordTypeSetWorldTransform)
	CASE(EmfPlusRecordTypeResetWorldTransform)
	CASE(EmfPlusRecordTypeMultiplyWorldTransform)
	CASE(EmfPlusRecordTypeTranslateWorldTransform)
	CASE(EmfPlusRecordTypeScaleWorldTransform)
	CASE(EmfPlusRecordTypeRotateWorldTransform)
	CASE(EmfPlusRecordTypeSetPageTransform)
	CASE(EmfPlusRecordTypeResetClip)
	CASE(EmfPlusRecordTypeSetClipRect)
	CASE(EmfPlusRecordTypeSetClipPath)
	CASE(EmfPlusRecordTypeSetClipRegion)
	CASE(EmfPlusRecordTypeOffsetClip)
	CASE(EmfPlusRecordTypeDrawDriverString)
#if (GDIPVER >= 0x0110)
	CASE(EmfPlusRecordTypeStrokeFillPath)
	CASE(EmfPlusRecordTypeSerializableObject)
	CASE(EmfPlusRecordTypeSetTSGraphics)
	CASE(EmfPlusRecordTypeSetTSClip)
#endif
	default:
		str = itoa(type, g_intBuffer, 10);
		break;
	}
	return str;
}
