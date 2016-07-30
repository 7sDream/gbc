//
// Created by i7sdream on 15-10-3.
//

#pragma once

#include <GL/freeglut.h>
#include <string>

namespace gbc{
    class GLText{
    private:
        std::string string;
        void* font;
    public:
        GLText(const std::string& s, void* f = GLUT_BITMAP_HELVETICA_12);
        GLText(const GLText& s);
        void* getFont() const;
        const unsigned char* getString() const;
    };
}