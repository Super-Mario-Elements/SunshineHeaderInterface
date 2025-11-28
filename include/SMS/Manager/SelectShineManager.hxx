#pragma once
#include <JSystem/JDrama/JDRGraphics.hxx>
#include <JSystem/JDrama/JDRViewObj.hxx>

class TSelectShineManager  : public JDrama::TViewObj {
public:
    TSelectShineManager(const char *name);
    virtual ~TSelectShineManager();

    virtual void perform(u32, JDrama::TGraphics *) override;

    void initData(u8 *, u8 *, u8, u8, void* /*JPAEmitterManager */);
    void startClose();
    void startDecrease(int);
    void startIncrease(int);
    
    /* TODO: Params */
    u32 _unk[0x90 / 4];
};