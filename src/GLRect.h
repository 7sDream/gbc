//
// Created by i7sdream on 15-10-24.
//

#pragma once

#include "GLLine3D.h"
#include "GLLoopline2D.h"

namespace gbc{
    class GLRect: public GLLoopline2D{
    private:
        GLPoint lefttop, rightdown;
    public:
        GLRect(const GLPoint & lefttop_, const GLPoint & rightdown_);
        GLRect(const double left, const double top, const double right, const double down);
    public:
        void setPoint(const double left, const double top, const double right, const double down);
        bool clipLine(GLLine3D &line) const;
    private:
        int computeCode(const GLPoint & point) const;
    };
}
