//
// Created by i7sdream on 15-9-28.
//

#include "GLPen.h"

namespace gbc{
    GLPen WhitePen(255, 255, 255, 1);
    GLPen BlackPen(0, 0, 0, 1);
    GLPen RedPen(255, 0, 0, 1);

    GLPen::GLPen(int red, int green, int blue, float size){
        setColor(red, green, blue);
        setSize(size);
    }

    void GLPen::setColor(int red, int green, int blue){
        r = red, g = green, b = blue;
    }

    void GLPen::setSize(float size){
        s = size;
    }

    void GLPen::clear(int r, int g, int b){
        glClearColor((float)r / 255, (float)g / 255, (float)b / 255, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void GLPen::flush(){
        glFlush();
        glutSwapBuffers();
    }

    void GLPen::iAmDefaultPen(){
        glColor3f((float)r / 255, (float)g / 255, (float)b / 255);
        glPointSize(s);
        glLineWidth(s);
        glPolygonMode(GL_FRONT_AND_BACK, polymode);
    }

    void GLPen::draw(const GLShape& shape){
        iAmDefaultPen();
        glBegin(shape.style());
        {
            shape.draw();
        }
        glEnd();
    }

    void GLPen::draw(const GLShape* shape){
        iAmDefaultPen();
        glBegin(shape->style());
        {
            shape->draw();
        }
        glEnd();
    }

    void GLPen::setPolygonMode(bool fill){
        if(fill){
            polymode = GL_FILL;
        }
        else{
            polymode = GL_LINE;
        }
    }

    void GLPen::draw(const GLText& text, int x, int y){
        iAmDefaultPen();
        glRasterPos2i(x, y);
        glutBitmapString(text.getFont(), text.getString());
    }
}
