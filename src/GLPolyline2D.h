//
// Created by i7sdream on 15-10-3.
//

#pragma once

#include "GLShape.h"
#include "GLPoint.h"
#include "GLShapeArray.h"
#include "GLShapeArray.cpp"

namespace gbc{
    class GLPolyline2D: public GLShape{
    private:
        GLShapeArray<GLPoint> points;
    public:
        GLPolyline2D();
        GLPolyline2D(const GLPolyline2D& polygon);
        GLPolyline2D(const GLShapeArray<GLPoint>& points_);
        GLPolyline2D(const std::vector<GLPoint>& points_);
        void assign(const GLPolyline2D& polygon);
        virtual GLenum style() const override;
        virtual void draw() const override;

        virtual std::vector<GLPoint *>::size_type size() const;

        virtual GLPolyline2D& addPoint(const GLPoint & point);
        virtual GLPolyline2D& addPoint(const double x, const double y);

        virtual const GLPoint & get(const typename std::vector<GLPoint *>::size_type i) const;
        virtual GLPoint & get(const typename std::vector<GLPoint *>::size_type i);

        virtual const std::vector<GLPoint *>& getConstPoints() const;
        virtual std::vector<GLPoint *>& getPoints();
        virtual void clear();
        virtual GLPolyline2D& rotate(const GLPoint & cp, double degree);
        virtual double minDistance(double x, double y, typename std::vector<GLPoint *>::size_type& pos) const;
        virtual void remove(std::vector<GLPoint *>::size_type pos);

        virtual void tweenTo(const GLPolyline2D& to, const double t, GLPolyline2D& mid) const;

        void prepareTween(const GLPolyline2D& muchPointPloyline);
    };
}