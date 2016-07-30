//
// Created by i7sdream on 15-9-28.
//

#include <glm/glm.hpp>
#include "GLPoint.h"
#include <iostream>

namespace gbc{

    GLPoint::GLPoint(double x_, double y_, double z_)
        : x(x_), y(y_), z(z_){
    }

    GLPoint::GLPoint(const double x[]){
        GLPoint(x[0], x[1], x[2]);
    }

    void GLPoint::draw() const{
        glVertex3d(x, y, z);
    }

    void GLPoint::set(double x_, double y_, double z_){
        x = x_, y = y_, z = z_;
    }

    GLPoint::~GLPoint(){
    }

    GLenum GLPoint::style() const{
        return GL_POINTS;
    }

    double GLPoint::getX() const{
        return x;
    }

    double GLPoint::getY() const{
        return y;
    }

    double GLPoint::getZ() const{
        return z;
    }

    void GLPoint::rotate(const GLPoint & cp, double degree){
        double cosa = std::cos(degree), sina = std::sin(degree);
        double x = cp.getX(), y = cp.getY();
        glm::mat3x3 rotate(cosa, -sina, (1 - cosa) * x + y * sina, sina, cosa, (1 - cosa) * y - x * sina, 0, 0, 1);
        transform(rotate);
    }

    void GLPoint::transform(const glm::mat3x3& matrix){
        glm::vec3 this_point(x, y, 1);
        glm::vec3 new_point = this_point * matrix;
        set(new_point[0], new_point[1]);
    }

    double GLPoint::distance(double x_, double y_, double z_) const{
        return std::sqrt(std::pow(x - x_, 2) + std::pow(y - y_, 2) + std::pow(z - z_, 2));
    }

    double GLPoint::distance(const GLPoint & p) const{
        return distance(p.x, p.y, p.z);
    }
}
