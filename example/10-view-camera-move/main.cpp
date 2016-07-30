#include <fstream>
#include <SDL2/SDL.h>
#include <iostream>
#include "GBC.h"

gbc::GLShapeArray<gbc::GLLoopline2D> ball;
gbc::GLShapeArray<gbc::GLLine3D> ground;

double eye[3] = {3, 3, 7};
double center[3] = {0, 0, 0};
double up[3] = {0, 1, 0};
double angle_y = 90;  // range -90 - 90;
double angle_z = 0;   // range 0 - 180;

double rotateAngleForTeaport = 0;
double rotateAngleForBall = 0;
double moveForBall = 0;
double moveForTeaport = 0;

double keyboardMoveTeaport[3] = {0, 0, 0};
double keyboardRotateTeaport = 0;

bool isBallMove = false;
bool isTeaportMove = false;

void calcCenter(){
    double y_rad = angle_y / 180.0 * M_PI;
    double z_rad = angle_z / 180.0 * M_PI;
    center[0] = eye[0] + std::cos(y_rad) * std::cos(z_rad);
    center[1] = eye[1] + std::sin(y_rad);
    center[2] = eye[2] - std::cos(y_rad) * std::sin(z_rad);
    up[0] = 0; //std::cos(y_rad + M_PI_2) * std::cos(z_rad);
    up[1] = 1; //std::sin(y_rad + M_PI_2);
    up[2] = 0; //- std::cos(y_rad + M_PI_2) * std::sin(z_rad);
}

void myDisplay(){
    gbc::GLPen greenPen(123, 200, 36, 1);
    gbc::GLPen bluePen(0, 0, 200, 1);
    gbc::BlackPen.clear(255, 255, 255);
    calcCenter();
    gbc::setViewPort3D(-1.2, 1.2, -1.2, 1.2, 0, 100, 0, 0, 640, 640);
    gluLookAt(eye[0], eye[1], eye[2],
              center[0], center[1], center[2],
              up[0], up[1], up[2]);

    bluePen.draw(ground);

    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0, 1, 0);
    glTranslatef(6*std::cos(moveForBall), 0, 6*std::sin(moveForBall));
    glRotated(rotateAngleForBall, 1, 0, 0);
    glRotated(rotateAngleForBall, 0, 1, 0);
    glRotated(rotateAngleForBall, 0, 0, 1);
    greenPen.draw(ball);
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0, 0.75, 0);
    glTranslatef(keyboardMoveTeaport[0], keyboardMoveTeaport[1], keyboardMoveTeaport[2]);
    glTranslatef(0, moveForTeaport <= 5 ? moveForTeaport : (10 - moveForTeaport), 0);
    glRotatef(rotateAngleForTeaport, 1, 0, 0);
    glRotatef(rotateAngleForTeaport + keyboardRotateTeaport, 0, 1, 0);
    glRotatef(rotateAngleForTeaport, 0, 0, 1);
    glutWireTeapot(1);
    glPopMatrix();

    gbc::BlackPen.flush();
}

void myMouseMotion(int x, int y){
    angle_y = 90 -  y / 640.0 * 180;
    angle_z = 180 - x / 640.0 * 180;
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
void myResize(int width, int height){
    glutReshapeWindow(640, 640);
}
#pragma clang diagnostic pop

void myMove(int x){
    gbc::callDisplay();
    if(!isBallMove && !isTeaportMove){
        return;
    }
    if(isBallMove){
        rotateAngleForBall += 1;
        moveForBall += M_PI / 180;
    }
    if(isTeaportMove){
        rotateAngleForTeaport += 3;
        moveForTeaport += 0.1;
        moveForTeaport = ((moveForTeaport >= 10) ? 0 : moveForTeaport);
    }
    gbc::setTimerFunc(myMove);
}

void myKeyboard(unsigned char key, int x, int y){
    switch(key){
        case 'q':{
            eye[1] += 0.1;
            break;
        }
        case 'a':{
            eye[0] -= 0.1;
            break;
        }
        case 'e':{
            eye[1] -= 0.1;
            break;
        }
        case 'd':{
            eye[0] += 0.1;
            break;
        }
        case 'w':{
            eye[2] -= 0.1;
            break;
        }
        case 's':{
            eye[2] += 0.1;
            break;
        }
        case 't':{
            isTeaportMove = !isTeaportMove;
            if(isTeaportMove && !isBallMove){
                gbc::setFlushFreq(16);
                gbc::setTimerFunc(myMove);
            }
            break;
        }
        case 'b':{
            isBallMove = !isBallMove;
            if(isBallMove && !isTeaportMove){
                gbc::setFlushFreq(16);
                gbc::setTimerFunc(myMove);
            }
            break;
        }
        case '5':{  // teaport up
            keyboardMoveTeaport[1] += 1;
            break;
        }
        case '2':{  // teaport down
            keyboardMoveTeaport[1] -= 1;
            break;
        }
        case '1':{  // teaport left
            keyboardMoveTeaport[0] -= 1;
            break;
        }
        case '3':{  // teaport right
            keyboardMoveTeaport[0] += 1;
            break;
        }
        case '8':{ // teaport in
            keyboardMoveTeaport[2] -= 1;
            break;
        }
        case '0':{  // teaport out
            keyboardMoveTeaport[2] += 1;
            break;
        }
        case '7':{  // teaport self rotate left
            keyboardRotateTeaport += 5;
            break;
        }
        case '9':{  // teaport self rotate right
            keyboardRotateTeaport -= 5;
            break;
        }
        default:{
            break;
        }
    }
}

void createShapes(char *filename){
    std::ifstream ifs(filename);
    gbc::MeshFile mesh(ifs);
    ball.getVector().assign(mesh.getFaces().getConstVector().begin(), mesh.getFaces().getConstVector().end());

    for(int i = -50; i <= 50; i++){
        ground.push(gbc::GLLine3D(i, 0, -50, i, 0, 50));
        ground.push(gbc::GLLine3D(-50, 0, i, 50, 0, i));
    }
}

int main(int argc, char *argv[]){
    SDL_Init(SDL_INIT_EVERYTHING);
    argc--, argv++;
    if(argc == 0){
        const SDL_MessageBoxButtonData buttonData[] {
                {0, 0, "OK"}
        };
        const SDL_MessageBoxData messageBoxData = {
                SDL_MESSAGEBOX_ERROR,
                NULL,
                "Error",
                "Need file name...",
                SDL_arraysize(buttonData),
                buttonData,
                NULL
        };
        int button_id;
        SDL_ShowMessageBox(&messageBoxData, &button_id);
        return 1;
    }
    else{
        createShapes(argv[0]);
    }

    gbc::init(argc, argv);
    gbc::setWindowSize(640, 640);
    gbc::createWindow("ball");
    gbc::fillWindow(255, 255, 255);

    gbc::setDisplayFunc(myDisplay);
    gbc::setResizeFunc(myResize);
    gbc::setPassiveMotionFunc(myMouseMotion);
    gbc::setKeyboardFunc(myKeyboard);

    gbc::showWindow();

    return 0;
}
