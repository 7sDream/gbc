//
// Created by i7sdream on 15-10-24.
//

#include "GLRect.h"

namespace gbc{
    GLRect::GLRect(const GLPoint & lefttop_, const GLPoint & rightdown_)
    : GLRect(lefttop_.getX(), lefttop_.getY(), rightdown_.getX(), rightdown_.getY()){

    }

    GLRect::GLRect(const double left, const double top, const double right, const double down)
    : lefttop(0, 0), rightdown(0, 0){
        setPoint(left, top, right, down);
    }

    bool GLRect::clipLine(GLLine3D &line) const{
        int start_code = computeCode(line.getStartPoint());
        int end_code = computeCode(line.getEndPoint());
        bool res = false;
        for(;;){
            if((start_code | end_code) == 0){
                res = true;
                break;
            }
            else if((start_code & end_code) != 0){
                break;
            }
            else{
                double x = 0, y = 0;
                int code = start_code ? start_code : end_code;
                GLPoint sp = line.getStartPoint();
                GLPoint ep = line.getEndPoint();
                if(code & 8){ // point above rect
                    y = lefttop.getY();
                    x = sp.getX() + (ep.getX() - sp.getX()) * (y - sp.getY()) / (ep.getY() - sp.getY());
                }
                else if(code & 4){  // point bellow rect
                    y = rightdown.getY();
                    x = sp.getX() + (ep.getX() - sp.getX()) * (y - sp.getY()) / (ep.getY() - sp.getY());
                }
                else if(code & 2){  // point at right of rect
                    x = rightdown.getX();
                    y = sp.getY() + (ep.getY() - sp.getY()) * (x - sp.getX()) / (ep.getX() - sp.getX());
                }
                else if(code & 1){
                    x = lefttop.getX();
                    y = sp.getY() + (ep.getY() - sp.getY()) * (x - sp.getX()) / (ep.getX() - sp.getX());
                }
                if(code == start_code){
                    line.setStartPoint(x, y, line.getStartPoint().getZ());
                    start_code = computeCode(line.getStartPoint());
                }
                else{
                    line.setEndPoint(x, y, line.getEndPoint().getZ());
                    end_code = computeCode(line.getEndPoint());
                }
            }
        }
        return res;
    }

    int GLRect::computeCode(const GLPoint & point) const{
        int code = 0;
        if(point.getX() < lefttop.getX()){
            code |= 1;
        }
        else if(point.getX() > rightdown.getX()){
            code |= 2;
        }
        if(point.getY() < rightdown.getY()){
            code |= 4;
        }
        else if(point.getY() > lefttop.getY()){
            code |= 8;
        }
        return code;
    }

    void GLRect::setPoint(const double left, const double top, const double right, const double down){
        assert(left != right && top != down);
        getPoints().clear();
        double xmin = left < right ? left : right;
        double xmax = left < right ? right : left;
        double ymin = down < top ? down : top;
        double ymax = down < top ? top : down;
        lefttop.set(xmin, ymax);
        rightdown.set(xmax, ymin);
        addPoint(lefttop);
        addPoint(xmin, ymin);
        addPoint(rightdown);
        addPoint(xmax, ymax);
    }
}