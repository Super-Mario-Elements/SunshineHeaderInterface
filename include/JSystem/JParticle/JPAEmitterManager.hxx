#pragma once

#include <JSystem/JParticle/JPAResourceManager.hxx>

class JPAEmitterManager {
public:
    JPAEmitterManager(JPAResourceManager*, s32, s32, s32, JKRHeap*);

    void calc();
    void calcBase(u8);
    /*bool createEmitter(TVec3f *, s32, JPACallBackBase *, JPACallBackBase2 *);
    JPABaseEmitter *createEmitterBase(s32, u8, u8, JPACallBackBase *, JPACallBackBase2 *);
    int createSimpleEmitterID(TVec3f *, s32, u8, u8, JPACallBackBase *, JPACallBackBase2 *);*/
    void deleteEmitter(JPABaseEmitter *);
    void draw(void * /* JPADrawInfo ptr */);
    void draw(void * /* JPADrawInfo ptr */, u8);
    void forceDeleteEmitter(JPABaseEmitter *);

    /* TODO properties */
    u32 _0[0x104/4]; 
};