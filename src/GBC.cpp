//
// Created by i7sdream on 15-9-30.
//

#include "GBC.h"

namespace gbc{
    unsigned int GBC_FREQ = 16;

    void init(int argc, char *argv[]){
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_POINT_SMOOTH);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_POLYGON_SMOOTH);
        glHint(GL_POINT_SMOOTH, GL_NICEST);
        glHint(GL_LINE_SMOOTH, GL_NICEST);
        glHint(GL_POLYGON_SMOOTH, GL_NICEST);
    }

    void setWindowPosition(int left, int top){
        glutInitWindowPosition(left, top);
    }

    void setWindowSize(int width, int height){
        int screen_width = glutGet(GLUT_SCREEN_WIDTH);
        int screen_height = glutGet(GLUT_SCREEN_HEIGHT);
        glutInitWindowSize(width, height);
        glutInitWindowPosition((screen_width - width) / 2, (screen_height - height) / 2);
    }

    void fillWindow(int r, int g, int b){
        glClearColor((float)r / 255, (float)g / 255, (float)b / 255, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glFlush();
        glutSwapBuffers();
    }

    void createWindow(const char *title){
        glutCreateWindow(title);
    }

    void showWindow(){
        glutMainLoop();
    }

    void setViewPort2D(double wl, double wr, double wd, double wt, int vx, int vy, int vw, int vh){
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(wl, wr, wd, wt);
        glViewport(vx, vy, vw, vh);
    }

    void setViewPort3D(double left, double right, double bottom, double top, double near, double far, int vx, int vy, int vw, int vh) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60, 640/480, 0, 10);
        glViewport(vx, vy, vw, vh);
    }

    void setIdleFunc(void (*callback)()){
        glutIdleFunc(callback);
    }

    void setDisplayFunc(void (*callback)()){
        glutDisplayFunc(callback);
    }

    void setTimerFunc(void (*callback)(int)){
        glutTimerFunc(GBC_FREQ, callback, GBC_FREQ);
    }

    void setFlushFreq(unsigned int t){
        GBC_FREQ = t;
    }

    void setResizeFunc(void (*callback)(int width, int height)){
        glutReshapeFunc(callback);
    }

    void callDisplay(){
        glutPostRedisplay();
    }

    void setKeyboardFunc(void (*callback)(unsigned char key, int x, int y)){
        glutKeyboardFunc(callback);
    }

    void setMouseFunc(void (*callback)(int, int, int, int)){
        glutMouseFunc(callback);
    }

    void setMotionFunc(void (*callback)(int x, int y)){
        glutMotionFunc(callback);
    }

    void setPassiveMotionFunc(void (* callback)(int x, int y)){
        glutPassiveMotionFunc(callback);
    }

    bool isContorlDown(){
        return (glutGetModifiers() & GLUT_ACTIVE_CTRL) != 0;
    }

    bool isAltDown(){
        return (glutGetModifiers() & GLUT_ACTIVE_ALT) != 0;
    }

    bool isShiftDown(){
        return (glutGetModifiers() & GLUT_ACTIVE_SHIFT) != 0;
    }
}
