#pragma once

#include <Dolphin/types.h>
#include <JSystem/J2D/J2DPane.hxx>
#include <JSystem/JSupport/JSUInputStream.hxx>

class J2DScreen : public J2DPane {
public:
    inline J2DScreen() : J2DPane() {}
    virtual ~J2DScreen();

    virtual void drawSelf(int, int, Mtx *);
    virtual J2DPane *search(u32 id);

    void makeHiearachyPanes(J2DPane *, JSURandomInputStream *, bool, bool, bool, s32 *);
    u32 makeUserPane(s16, J2DPane *, JSURandomInputStream *);
    u32 makeUserPane(u32, J2DPane *, JSURandomInputStream *);

    void stop();
    void draw(int x, int y, const J2DGrafContext *context);

    u8 _EC;
    u32 _D0;
    u8 _D4[0xF0 - 0xD4];
    u32 _F0;
};
