#pragma once

#include <SMS/sound/MSound.hxx>
#include <SMS/sound/JAIAnimeSound.hxx>

class MAnmSound : public JAIAnimeSound
{
    public:
    MAnmSound(MSound *); // MSound *

    void startAnimSound(void *, u32, JAISound **, u32 *, u8); // JAIActor *
    void setSpeedModifySound(JAISound *, u32 *, f32); // JAIAnimeFrameSoundData *
};