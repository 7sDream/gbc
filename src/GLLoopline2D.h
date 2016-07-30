//
// Created by i7sdream on 15-9-29.
//

#pragma once

#include "GLPoint.h"
#include "GLPolyline2D.h"
#include "GLLine3D.h"
#include <vector>

namespace gbc{
    class GLLoopline2D: public GLPolyline2D{
    public:
        GLLoopline2D();
        GLLoopline2D(const GLLoopline2D& polygon);
        GLLoopline2D(const GLShapeArray<GLPoint>& points_);
        GLLoopline2D(const std::vector<GLPoint>& points_);
        void assign(const GLLoopline2D& polygon);
        virtual GLenum style() const override;
        virtual GLLoopline2D& addPoint(const GLPoint & point) override;
        virtual GLLoopline2D& addPoint(const double x, const double y) override;
        virtual bool clipLine(GLLine3D &line, bool clockwise=true) const;
        GLLoopline2D& rotate(const GLPoint & cp, double degree);
    };
}
