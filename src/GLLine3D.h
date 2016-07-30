//
// Created by i7sdream on 15-9-28.
//

#pragma once

#include "GLShape.h"
#include "GLPoint.h"

namespace gbc{
    class GLLine3D : public GLShape{
    private:
        double startx, starty, startz, endx, endy, endz;
    public:
        GLLine3D(const GLLine3D & line);
        GLLine3D(double startx, double starty, double startz, double endx, double endy, double endz);
        GLLine3D(const GLPoint & start, const GLPoint & end);
        GLLine3D(const double x[]);
        virtual void draw() const override;
        virtual GLenum style() const override;
        GLPoint getStartPoint() const;
        GLPoint getEndPoint() const;
        void setStartPoint(const double x, const double y, const double z);
        void setEndPoint(const double x, const double y, const double z);
        GLPoint midPoint() const;
    };
}
