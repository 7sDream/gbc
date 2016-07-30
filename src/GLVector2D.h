//
// Created by i7sdream on 15-11-16.
//

# pragma once

#include "GLLine3D.h"
#include "GLPoint.h"

namespace gbc{
    class GLVector2D {
    public:
        static const int VER_CLOCKWISE = 0;
        static const int PAR = 1;
        static const int VER_ANTICLOCKWISE = 2;
    private:
        double a, b;
    public:
        GLVector2D(double a_ = 0, double b_ = 0);
        GLVector2D(const GLPoint & start, const GLPoint & end);
        GLVector2D(const GLLine3D & line, int MODE=PAR);

        double getA() const;
        double getB() const;
        double operator*(const GLVector2D& rhs);
    };
}

