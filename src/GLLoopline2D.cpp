//
// Created by i7sdream on 15-9-29.
//

#include <glm/glm.hpp>
#include "GLVector2D.h"
#include "GLLoopline2D.h"

namespace gbc{
    GLLoopline2D::GLLoopline2D()
        : GLPolyline2D(){
    }

    GLLoopline2D::GLLoopline2D(const GLLoopline2D& polygon)
        : GLPolyline2D(polygon){
    }

    void GLLoopline2D::assign(const GLLoopline2D& polygon){
        GLPolyline2D::assign(polygon);
    }

    GLLoopline2D::GLLoopline2D(const GLShapeArray<GLPoint>& points_)
        : GLPolyline2D(points_){
    }

    GLLoopline2D::GLLoopline2D(const std::vector<GLPoint>& points_)
        : GLPolyline2D(points_){
    }

    GLenum GLLoopline2D::style() const{
        return GL_LINE_LOOP;
    }

    GLLoopline2D& GLLoopline2D::addPoint(const GLPoint & point){
        GLPolyline2D::addPoint(point);
        return *this;
    }

    GLLoopline2D& GLLoopline2D::addPoint(const double x, const double y){
        GLPolyline2D::addPoint(x, y);
        return *this;
    }

    GLLoopline2D& GLLoopline2D::rotate(const GLPoint & cp, double degree){
        GLPolyline2D::rotate(cp, degree);
        return *this;
    }

    bool GLLoopline2D::clipLine(GLLine3D &line, bool clockwise) const {
        std::vector<GLPoint *> ps(getConstPoints());
        GLPoint *dend = new GLPoint(get(0));
        ps.push_back(dend);
        GLVector2D c(line, GLVector2D::PAR);

        double in = 0, out = 1;
        GLPoint start = *ps.at(0);
        for(size_t i = 1; i < ps.size(); i++){
            GLPoint end = *ps.at(i);
            GLVector2D n;
            if(clockwise)
                n = GLVector2D(GLLine3D(start, end), GLVector2D::VER_CLOCKWISE);
            else
                n = GLVector2D(GLLine3D(start, end), GLVector2D::VER_ANTICLOCKWISE);
            GLVector2D x(line.getStartPoint(), start);
            double nc = n * c;
            if(nc != 0){
                double t = n * x / nc;
                if(nc < 0){ // enter
                    in = t > in ? t : in;
                }
                else{       // out
                    out = t < out ? t : out;
                }
            }
            if(in > out){
                delete dend;
                return false;
            }
            start = end;
        }
        line.setEndPoint(line.getStartPoint().getX() + out * c.getA(), line.getStartPoint().getY() + out * c.getB(), line.getEndPoint().getZ());
        line.setStartPoint(line.getStartPoint().getX() + in * c.getA(), line.getStartPoint().getY() + in * c.getB(), line.getStartPoint().getZ());
        return true;
    }
}
