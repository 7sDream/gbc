#include <fstream>
#include <SDL2/SDL.h>
#include "GBC.h"

gbc::GLShapeArray<gbc::GLLoopline2D> ball;

double eye[3] = {0, 0, 2.5};
double center[3] = {0, 0, 0};
double up[3] = {0, 1, 0};
double angle_y = 90;  // range -90 - 90;
double angle_z = 0;   // range 0 - 180;

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
    gbc::GLPen pen(123, 200, 36, 1);
    gbc::BlackPen.clear(0, 0, 0);
    calcCenter();
    gbc::setViewPort3D(-1.2, 1.2, -1.2, 1.2, 0, 100, 0, 0, 640, 640);
    gluLookAt(eye[0], eye[1], eye[2],
              center[0], center[1], center[2],
              up[0], up[1], up[2]);
    pen.draw(ball);
    glutWireTeapot(0.5);
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

void myKeyboard(unsigned char key, int x, int y){
    switch(key){
        case 'w':{
            eye[1] += 0.1;
            break;
        }
        case 'a':{
            eye[0] -= 0.1;
            break;
        }
        case 's':{
            eye[1] -= 0.1;
            break;
        }
        case 'd':{
            eye[0] += 0.1;
            break;
        }
        default:{
            break;
        }
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
        std::ifstream ifs(argv[0]);
        gbc::MeshFile mesh(ifs);
        ball.getVector().assign(mesh.getFaces().getConstVector().begin(), mesh.getFaces().getConstVector().end());
    }

    gbc::init(argc, argv);
    gbc::setWindowSize(640, 640);
    gbc::createWindow("ball");
    gbc::fillWindow(0, 0, 0);

    gbc::setDisplayFunc(myDisplay);
    gbc::setResizeFunc(myResize);
    gbc::setPassiveMotionFunc(myMouseMotion);
    gbc::setKeyboardFunc(myKeyboard);

    gbc::showWindow();

    return 0;
}
