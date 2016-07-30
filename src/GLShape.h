//
// Created by i7sdream on 15-9-28.
//

#pragma once

#include <GL/freeglut.h>

namespace gbc{
    class GLShape{
    public:
        GLShape();
        virtual ~GLShape();
        virtual void draw() const = 0;
        virtual GLenum style() const = 0;
    };
}
