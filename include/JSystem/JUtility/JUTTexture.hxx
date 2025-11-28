#pragma once

#include <Dolphin/GX.h>
#include <Dolphin/types.h>

#include <JSystem/JKernel/JKRFileLoader.hxx>
#include <JSystem/JUtility/JUTPalette.hxx>

struct ResTIMG {
    enum EFormat {
        I4     = 0,
        I8     = 1,
        IA4    = 2,
        IA8    = 3,
        RGB565 = 4,
        RGB5A3 = 5,
        RGBA32 = 6,
        C4     = 8,
        C8     = 9,
        C14X2  = 10,
        CMPR   = 14
    };

    enum EWrapMode { ClampToEdge, Repeat, MirroredRepeat };

    enum EFilterMode {
        Nearest,
        Linear,
        NearestMipmapNearest,
        NearestMipmapLinear,
        LinearMipmapNearest,
        LinearMipmapLinear
    };

    u8 mFormat;
    u8 mAlphaSetting;
    u16 mWidth;
    u16 mHeight;
    u8 mWrapSMode;
    u8 mWrapTMode;
    bool mHasPalette;
    u8 mPaletteFormat;
    u16 mPaletteColors;
    s32 mPaletteOffset;
    u32 _10;
    u8 mFilterMinMode;
    u8 mFilterMagMode;
    u8 mLODMin;
    u8 mLODMag;
    u8 mMipMaps;
    u16 mLODBias;
    s32 mTextureOffset;
};

class JUTTexture {
public:
    inline JUTTexture() {}
    inline JUTTexture(const char *resource) {
        auto *timg = reinterpret_cast<const ResTIMG *>(JKRFileLoader::getGlbResource(resource));
		mEmbPalette = nullptr;
		storeTIMG(timg);
		unk50 = 0;
    }
    JUTTexture(int sX, int sY, GXTexFmt format);
    ~JUTTexture();

    void attachPalette(JUTPalette *palette);
    void initTexObj(GXTlut tlut);
    void initTexObj();
    void load(GXTexMapID id);
    void storeTIMG(const ResTIMG *timg);
    
	/* 0x00 */ GXTexObj mTexObj;
	/* 0x20 */ const ResTIMG* mTexInfo;
	/* 0x24 */ void* mTexData;
	/* 0x28 */ JUTPalette* mEmbPalette;
	/* 0x2C */ JUTPalette* field_0x2c;
	/* 0x30 */ u32 mTlutName;
	/* 0x34 */ u32 mFormat;
	/* 0x38 */ u32 mAlphaEnabled;
	/* 0x3C */ u16 mWidth;
	/* 0x3E */ u16 mHeight;
	/* 0x40 */ u8 mWrapS;
	/* 0x41 */ u8 mWrapT;
	/* 0x42 */ u8 mMinFilter;
	/* 0x43 */ u8 mMagFilter;
	/* 0x44 */ u16 mMinLOD;
	/* 0x46 */ u16 mMaxLOD;
	/* 0x48 */ s16 mLODBias;
	/* 0x4B */ u8 mFlags;
	/* 0x4C */ void* field_0x4c;
	/* 0x50 */ u8 unk50;

    // 4C = GXTexFmt
};