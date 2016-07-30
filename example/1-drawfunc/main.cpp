#include <cmath>
#include "GBC.h"

double X_MIN = -20;
double X_MAX = 20;
double Y_MIN = -0.8;
double Y_MAX = 1.2;
double X_STEP = 0.01;
double X_TICK_STEP = 1;
double Y_TICK_STEP = 0.1;

// axis points
double MAIN_AXIS[] = {
        0, Y_MIN, 0, 0, Y_MAX, 0, // y axis
        X_MIN, 0, 0, X_MAX, 0, 0 // x axis
};

gbc::GLShapeArray<gbc::GLPoint> points;
gbc::GLShapeArray<gbc::GLLine3D> lines;

void createPointsAndLines(){
    // create function points
    for(double i = X_MIN; i <= X_MAX; i += X_STEP){
        points.push(gbc::GLPoint(i, std::sin(i) / i));
    }

    // create x, y axis
    lines.push(gbc::GLLine3D(MAIN_AXIS));
    lines.push(gbc::GLLine3D(MAIN_AXIS+6));

    // create x ticks
    for(double i = 0; i <= std::max(std::abs(X_MIN), std::abs(X_MAX)); i += X_TICK_STEP){
        if(i <= X_MAX){
            lines.push(gbc::GLLine3D(i, 0, 0, i, 0.03, 0));
        }
        if(-i >= X_MIN){
            lines.push(gbc::GLLine3D(-i, 0, 0, -i, 0.03, 0));
        }
    }

    // create y ticks
    for(double i = 0; i <= std::max(std::abs(Y_MIN), std::abs(Y_MAX)); i += Y_TICK_STEP){
        if(i <= Y_MAX)
            lines.push(gbc::GLLine3D(0, i, 0, 0.3, i, 0));
        if(-i >= Y_MIN)
            lines.push(gbc::GLLine3D(0, -i, 0, 0.3, -i, 0));
    }
}

void myDisplay(){
    gbc::BlackPen.clear(255, 255, 255);

    gbc::BlackPen.setSize(2);
    gbc::BlackPen.draw(points);

    gbc::BlackPen.setSize(1);
    gbc::BlackPen.draw(lines);

    gbc::BlackPen.flush();
}

int main(int argc, char *argv[]){
    gbc::init(argc, argv);
    gbc::setWindowSize(640, 480);
    gbc::createWindow("grapg of Sin[x]/x in range [-20, 20]");
    gbc::fillWindow(255, 255, 255);
    gbc::setViewPort2D(-20, 20, -0.8, 1.2, 0, 0, 640, 480);

    createPointsAndLines();

    gbc::setDisplayFunc(myDisplay);

    gbc::showWindow();

    return 0;
}
