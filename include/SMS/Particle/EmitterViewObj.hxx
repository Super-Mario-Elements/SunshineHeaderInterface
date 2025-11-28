#pragma once 

#include <JDrama/JDRViewObj.hxx>
#include <JSystem/JParticle/JPAEmitterManager.hxx>

class TEmitterViewObj : public JDrama::TViewObj {
public:
    TEmitterViewObj(JPAEmitterManager *, const char *);
    virtual ~TEmitterViewObj();
    
    virtual void perform(u32, JDrama::TGraphics *) override;

    JPAEmitterManager *mEmitterManager;
};