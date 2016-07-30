//
// Created by i7sdream on 15-9-28.
//

#include "GLLine3D.h"

namespace gbc{
    GLLine3D::GLLine3D(const GLLine3D & line)
        : startx(line.startx), starty(line.starty), startz(line.startz),
          endx(line.endx), endy(line.endy), endz(line.endz){
    }

    GLLine3D::GLLine3D(double startx_, double starty_, double startz_, double endx_, double endy_, double endz_)
        : startx(startx_), starty(starty_), startz(startz_), endx(endx_), endy(endy_), endz(endz_){
    }

    GLLine3D::GLLine3D(const GLPoint & start, const GLPoint & end)
        : startx(start.getX()), starty(start.getY()), startz(start.getZ()),
          endx(end.getX()), endy(end.getY()), endz(end.getZ()){
    }

    GLLine3D::GLLine3D(const double x[])
        : startx(x[0]), starty(x[1]), startz(x[2]),
          endx(x[3]), endy(x[4]), endz(x[5]){
    }

    void GLLine3D::draw() const{
        glVertex3d(startx, starty, startz);
        glVertex3d(endx, endy, endz);
    }

    GLenum GLLine3D::style() const{
        return GL_LINES;
    }

    GLPoint GLLine3D::getStartPoint() const{
        return GLPoint(startx, starty, startz);
    }

    GLPoint GLLine3D::getEndPoint() const{
        return GLPoint(endx, endy, endz);
    }

    void GLLine3D::setStartPoint(const double x, const double y, const double z){
        startx = x;
        starty = y;
        startz = z;
    }

    void GLLine3D::setEndPoint(const double x, const double y, const double z){
        endx = x;
        endy = y;
        endz = z;
    }

    GLPoint GLLine3D::midPoint() const{
        return gbc::GLPoint((startx + endx) / 2, (starty + endy) / 2, (startz + endz) / 2);
    }
}
