//
// Created by i7sdream on 15-9-28.
//

#pragma once

#include <vector>
#include "GLShape.h"
#include "GLShapeArray.h"
#include "GLText.h"

namespace gbc{
    class GLPen{
    private:
        int r, g, b;
        float s;
        GLenum polymode = GL_LINE;
    public:
        GLPen(int red, int green, int blue, float size);
        void setColor(int red, int green, int blue);
        void setSize(float size);
        void setPolygonMode(bool fill);
        void clear(int r, int g, int b);
        void flush();
        void draw(const GLShape& shape);
        void draw(const GLShape* shape);

        template<typename T>
        void draw(const GLShapeArray<T>& shapes){
            if(!shapes.getConstVector().empty()){
                iAmDefaultPen();
                for(auto& i : shapes.getConstVector()){
                    glBegin(i->style());
                    {
                        i->draw();
                    }
                    glEnd();
                }
            }
        };

        void draw(const GLText& text, int x, int y);

    private:
        void iAmDefaultPen();
    };

    extern GLPen WhitePen;
    extern GLPen BlackPen;
    extern GLPen RedPen;
}
