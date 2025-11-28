#pragma once

#include <MTX.h>
#include <Dolphin/types.h>
#include <JSystem/JDrama/JDRRect.hxx>

namespace JDrama {

    class TGraphics {
    public:
        void setViewport(const TRect &, f32, f32);

        u8 _00[0x20];
        bool _20;
        u8 _21[0x54 - 0x21];
        TRect mViewPortSpace;
        u32 _64[(0xb4 - 0x64) / 4];
        Mtx mWorldToScreen;
        u32 _b8[(0xf0 - 0xe4) / 4];
    };

}  // namespace JDrama