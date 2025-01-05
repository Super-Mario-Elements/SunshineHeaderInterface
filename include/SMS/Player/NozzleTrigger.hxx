#pragma once

#include <Dolphin/types.h>
#include <SMS/Player/NozzleBase.hxx>

class TNozzleTrigger : public TNozzleBase {

public:
    enum SPRAYSTATE { INACTIVE, ACTIVE, DEAD };

    bool mRunbleOnCharge;         // 0x0384
    u8 mSprayState;               // 0x0385
    s16 mSprayQuarterFramesLeft;  // 0x0386
    f32 mTriggerFill;             // 0x0388
    u32 mSoundID;                 // 0x038C
};