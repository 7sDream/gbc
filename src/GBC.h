//
// Created by i7sdream on 15-9-28.
//

#pragma once

#include "GLShape.h"
#include "GLPoint.h"
#include "GLLine3D.h"
#include "GLLoopline2D.h"
#include "GLRect.h"

#include "GLShapeArray.h"
#include "GLShapeArray.cpp"

#include "MeshFile.h"

#include "GLPen.h"

namespace gbc{
    extern unsigned int GBC_FREQ;

    // window init
    void init(int argc, char* argv[]);

    void setWindowSize(int width, int height);

    void setWindowPosition(int left, int top);

    void createWindow(const char* title);

    void fillWindow(int r, int g, int b);

    void setViewPort2D(double wl, double wr, double wt, double wd, int vl, int vr, int vt, int vd);

    void setViewPort3D(double left, double right, double bottom, double top, double near, double far, int vl, int vr, int vt, int vd);

    void showWindow();

    // func setting
    void setIdleFunc(void (* callback)(void));

    void setDisplayFunc(void (* callback)(void));

    void setFlushFreq(unsigned int t);

    void setResizeFunc(void (* callback)(int width, int height));

    void setTimerFunc(void (* callback)(int));

    void setKeyboardFunc(void (* callback)(unsigned char key, int x, int y));

    void setMouseFunc(void (* callback)(int, int, int, int));

    void setMotionFunc(void (* callback)(int x, int y));

    void setPassiveMotionFunc(void (* callback)(int x, int y));

    bool isContorlDown();

    bool isAltDown();

    bool isShiftDown();

    void callDisplay();
}
