#pragma once

#include <JSystem/JDrama/JDRViewObj.hxx>

#include <SMS/M3DUtil/MActor.hxx>

class TBeamManager : public JDrama::TViewObj {
public:
    TBeamManager(const char *name);

    void perform(u32, JDrama::TGraphics *) override;

    void requestCone(const TVec3f &, const TVec3f &, f32, bool, bool, bool);
    void setupMaterial();

    u32 data[0x3b4/4];
};

extern TBeamManager *gpBeamManager;