//
// Created by i7sdream on 15-11-16.
//

#include "GLVector2D.h"

namespace gbc{
    GLVector2D::GLVector2D(double a_, double b_)
    :a(a_), b(b_){
    }

    GLVector2D::GLVector2D(const GLPoint &start, const GLPoint &end)
    :a(end.getX() - start.getX()), b(end.getY() - start.getY()){
    }

    GLVector2D::GLVector2D(const GLLine3D &line, int MODE) {
        a = line.getEndPoint().getX() - line.getStartPoint().getX();
        b = line.getEndPoint().getY() - line.getStartPoint().getY();
        if(MODE == VER_CLOCKWISE){
            double temp = a;
            a = b, b = -temp;
        }
        else if(MODE == VER_ANTICLOCKWISE) {
            double temp = a;
            a = -b; b = temp;
        }
        else{
            assert(MODE == PAR);
        }
    }

    double GLVector2D::getA() const{
        return a;
    }

    double GLVector2D::getB() const{
        return b;
    }

    double GLVector2D::operator*(const GLVector2D &rhs) {
        return a * rhs.a + b * rhs.b;
    }
}
