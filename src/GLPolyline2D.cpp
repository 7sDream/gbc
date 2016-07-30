//
// Created by i7sdream on 15-10-3.
//

#include <glm/glm.hpp>
#include "GLPolyline2D.h"
#include "GLLine3D.h"

namespace gbc{
    GLPolyline2D::GLPolyline2D(){
    }

    GLPolyline2D::GLPolyline2D(const GLPolyline2D &polygon){
        assign(polygon);
    }

    void GLPolyline2D::assign(const GLPolyline2D& polygon){
        points.clear();
        for(auto &i : polygon.getConstPoints()){
            points.push(*i);
        }
    }

    GLPolyline2D::GLPolyline2D(const GLShapeArray<GLPoint> &points_){
        for(auto &i : points_.getConstVector()){
            points.push(*i);
        }
    }

    GLPolyline2D::GLPolyline2D(const std::vector<GLPoint> &points_){
        for(auto &i : points_){
            points.push(i);
        }
    }

    GLenum GLPolyline2D::style() const{
        return GL_LINE_STRIP;
    }

    void GLPolyline2D::draw() const{

        points.draw();
    }

    GLPolyline2D& GLPolyline2D::addPoint(const GLPoint &point){
        points.push(point);
        return *this;
    }

    GLPolyline2D& GLPolyline2D::addPoint(const double x, const double y){
        points.push(GLPoint(x, y));
        return *this;
    }

    const GLPoint & GLPolyline2D::get(const typename std::vector<GLPoint *>::size_type i) const{
        return points.get(i);
    }

    GLPoint & GLPolyline2D::get(const typename std::vector<GLPoint *>::size_type i){
        return points.get(i);
    }

    const std::vector<GLPoint *>& GLPolyline2D::getConstPoints() const{
        return points.getConstVector();
    }

    std::vector<GLPoint *>& GLPolyline2D::getPoints(){
        return points.getVector();
    }

    GLPolyline2D& GLPolyline2D::rotate(const GLPoint &cp, double degree){
        double cosa = std::cos(-degree), sina = std::sin(-degree);
        double x = cp.getX(), y = cp.getY();
        glm::mat3x3 rotate(cosa, -sina, (1 - cosa) * x + y * sina, sina, cosa, (1 - cosa) * y - x * sina, 0, 0, 1);
        for(auto i : points.getVector()){
            i->transform(rotate);
        }
        return *this;
    }

    double GLPolyline2D::minDistance(double x, double y, typename std::vector<GLPoint *>::size_type &pos) const{
        double res = std::numeric_limits<double>::max();
        for(size_t i = 0; i < points.size(); i++){
            double dis = points.get(i).distance(x, y, 0);
            if (dis < res){
                res = dis;
                pos = i;
            }
        }
        return res;
    }

    void GLPolyline2D::remove(std::vector<GLPoint *>::size_type pos){
        if(pos < points.size()){
            points.remove(pos);
        }
    }

    std::vector<GLPoint *>::size_type GLPolyline2D::size() const{
        return points.size();
    }

    void GLPolyline2D::prepareTween(const GLPolyline2D& muchPointPloyline){
        assert(size() <= muchPointPloyline.size());
        decltype(points.size()) i = 0;
        while(size() < muchPointPloyline.size()){
            if(i + 1 >= size()){
                points.insert(i+1, GLLine3D(get(i), get(0)).midPoint());
                i = 0;
            }
            else{
                points.insert(i+1, GLLine3D(get(i), get(i + 1)).midPoint());
                i += 2;
            }
        }
    }

    void GLPolyline2D::tweenTo(const GLPolyline2D& to, const double t, GLPolyline2D& mid) const{
        assert(size() == to.size());
        mid.clear();
        for(decltype(size()) i = 0; i < size(); i++){
            mid.addPoint(get(i).getX() + t * (to.get(i).getX() - get(i).getX()),
                         get(i).getY() + t * (to.get(i).getY() - get(i).getY()));
        }
    }

    void GLPolyline2D::clear(){
        points.clear();
    }
}
