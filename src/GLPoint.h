//
// Created by i7sdream on 15-9-28.
//

#pragma once

#include <glm/glm.hpp>
#include <GL/freeglut.h>
#include "GLShape.h"

namespace gbc{
    class GLPoint : public GLShape{
    private:
        double x, y, z;
    public:
        GLPoint(double x_, double y_, double z_=0);
        GLPoint(const double x[]);
        virtual ~GLPoint();
        void set(double x_, double y_, double z_=0);
        double getX() const;
        double getY() const;
        double getZ() const;
        void rotate(const GLPoint & cp, double degree);
        void transform(const glm::mat3x3& rotate_matrix);
        virtual void draw() const override;
        virtual GLenum style() const override;
        virtual double distance(double x, double y, double z) const;
        virtual double distance(const GLPoint & p) const;
    };
}
