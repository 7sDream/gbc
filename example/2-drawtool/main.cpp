#include <iostream>
#include "GBC.h"

/***************
 * Global vars *
 **************/

// ====== MODE enum and string =====

enum Mode{
    NORMAL, LOOPLINE, POLYLINE, MOVE, MOVING, DELETE, RECTCLIP, POLYGONCLIP, FLASH
}mode = NORMAL;

gbc::GLText modeString[] = {{"NORMAL MODE"},
                            {"LOOPLINE MODE"},
                            {"POLYLINE MODE"},
                            {"MOVE MODE"},
                            {"MOVING MODE"},
                            {"DELETE MODE"},
                            {"RECT CLIP"},
                            {"POLYGEN CLIP"},
                            {"FLASH MODE"}};

// ====== Shape library =====

gbc::GLShapeArray<gbc::GLPolyline2D> polylines;
gbc::GLShapeArray<gbc::GLLoopline2D> looplines;

// ===== shape for temply use when in draw mode =====

gbc::GLPolyline2D temppl;   // temp PolyLine
gbc::GLLoopline2D templl;   // temp LoopLine

// ===== point and rect for temply use in clip mode =====

gbc::GLPoint clip_point(-1, -1, 0);
gbc::GLRect clip_rect(0, 1, 2, 3);

gbc::GLShapeArray<gbc::GLLine3D> cliped_lines;

// ===== shape type, point index for moving mode =====

size_t moving_shape_type = 0, moving_shape_pos = 0, moving_point_pos = 0;

// temply shape for flash mode

gbc::GLLoopline2D flash_start, flash_end, flash_mid;
double flash_t;
bool reverse = false;

/************************
 * Function declaration *
 ************************/

void myKeyboard(unsigned char key, int x, int y);

/*************************
 * Functions definitions *
 *************************/

gbc::GLText modeToText(Mode mode){
    return modeString[static_cast<int>(mode)];
}

template<typename T>
double calcNearPoint(gbc::GLShapeArray<T> shapes, int x, int y, size_t& shape_pos, size_t& point_pos){
    double minDis = std::numeric_limits<double>::max();
    size_t size = shapes.size();
    for(size_t i = 0; i < size; i++){
        size_t temp_point_pos = 0;
        double dis = shapes.get(i).minDistance(x, y, temp_point_pos);
        if(dis < minDis){
            shape_pos = i;
            point_pos = temp_point_pos;
            minDis = dis;
        }
    }
    return minDis;
}

std::vector<size_t> getNearPoint(int x, int y){
    double polyline_dis = std::numeric_limits<double>::max(), loopline_dis = polyline_dis;
    size_t polyline_shape_pos = 0, polyline_point_pos = 0, loopline_shape_pos = 0, loopline_point_pos = 0;
    if(polylines.size() > 0 || looplines.size() > 0){
        if(polylines.size() > 0){
            polyline_dis = calcNearPoint<gbc::GLPolyline2D>(polylines, x, y, polyline_shape_pos, polyline_point_pos);
        }
        if(looplines.size() > 0){
            loopline_dis = calcNearPoint<gbc::GLLoopline2D>(looplines, x, y, loopline_shape_pos, loopline_point_pos);
        }
        if(polyline_dis < loopline_dis && polyline_dis <= 10){
            std::vector<size_t> res = {1, polyline_shape_pos, polyline_point_pos};
            return res;
        }
        else if(loopline_dis <= 10){
            std::vector<size_t> res = {2, loopline_shape_pos, loopline_point_pos};
            return res;
        }
    }
    std::vector<size_t> res = {0};
    return res;
}

void deletePoint(int x, int y){
    std::vector<size_t> point_data = getNearPoint(x, y);
    if(point_data.at(0) == 0){
        return;
    }
    else if(point_data.at(0) == 1){
        polylines.get(point_data.at(1)).remove(point_data.at(2));
        if(polylines.get(point_data.at(1)).size() <= 1){
            polylines.remove(point_data.at(1));
        }
    }
    else if(point_data.at(0) == 2){
        looplines.get(point_data.at(1)).remove(point_data.at(2));
        if(looplines.get(point_data.at(1)).size() <= 1){
            looplines.remove(point_data.at(1));
        }
    }
}

void getClipedLines(const gbc::GLRect& rect){
    auto& polylines_vec = polylines.getConstVector();
    for(auto polyline : polylines_vec){
        gbc::GLPoint start = polyline->get(0);
        for(auto i = 1; i < polyline->size(); i++){
            gbc::GLPoint end = polyline->get(i);
            gbc::GLLine3D line(start, end);
            start = end;
            bool flag = rect.clipLine(line);
            if(flag){
                cliped_lines.push(line);
            }
        }
    }
    auto& loopline_vec = looplines.getConstVector();
    for(auto loopline : loopline_vec){
        loopline->addPoint(loopline->get(0));
        gbc::GLPoint start = loopline->get(0);
        for(auto i = 1; i < loopline->size(); i++){
            gbc::GLPoint end = loopline->get(i);
            gbc::GLLine3D line(start, end);
            start = end;
            bool flag = rect.clipLine(line);
            if(flag){
                cliped_lines.push(line);
            }
        }
        loopline->remove(loopline->size() - 1);
    }
}

void getClipedLines(const gbc::GLLoopline2D& polygon){
    auto& polylines_vec = polylines.getConstVector();
    for(auto polyline : polylines_vec){
        gbc::GLPoint start = polyline->get(0);
        for(auto i = 1; i < polyline->size(); i++){
            gbc::GLPoint end = polyline->get(i);
            gbc::GLLine3D line(start, end);
            start = end;
            bool flag = polygon.clipLine(line);
            if(flag){
                cliped_lines.push(line);
            }
            else{
                flag = polygon.clipLine(line, false);
                if(flag){
                    cliped_lines.push(line);
                }
            }
        }
    }
    auto& loopline_vec = looplines.getConstVector();
    for(auto loopline : loopline_vec){
        loopline->addPoint(loopline->get(0));
        gbc::GLPoint start = loopline->get(0);
        for(auto i = 1; i < loopline->size(); i++){
            gbc::GLPoint end = loopline->get(i);
            gbc::GLLine3D line(start, end);
            start = end;
            bool flag = polygon.clipLine(line);
            if(flag){
                cliped_lines.push(line);
            }
            else{
                flag = polygon.clipLine(line, false);
                if(flag){
                    cliped_lines.push(line);
                }
            }
        }
        loopline->remove(loopline->size() - 1);
    }
}

void myDisplay(){
    gbc::BlackPen.clear(255, 255, 255);
    gbc::BlackPen.draw(modeToText(mode), 0, 12);
    if(mode != FLASH){
        gbc::BlackPen.draw(polylines);
        gbc::BlackPen.draw(looplines);
        gbc::BlackPen.draw(temppl);
        if(mode == RECTCLIP || mode == POLYGONCLIP){
            if(mode == RECTCLIP)
                gbc::BlackPen.draw(clip_rect);
            if(cliped_lines.size() > 0){
                gbc::RedPen.setSize(3);
                gbc::RedPen.draw(cliped_lines);
                gbc::RedPen.setSize(1);
            }
        }
    }
    else{
        gbc::BlackPen.draw(flash_start);
        gbc::BlackPen.draw(flash_mid);
        gbc::BlackPen.draw(flash_end);
    }
    gbc::BlackPen.flush();
}

void flashFunc(int t){
    if(mode == FLASH){
        gbc::callDisplay();
        flash_t += 0.01;
        if(!reverse){
            flash_start.tweenTo(flash_end, flash_t, flash_mid);
        }
        else{
            flash_end.tweenTo(flash_start, flash_t, flash_mid);
        }
        if(flash_t > 1){
            flash_t = 0;
            reverse = !reverse;
            gbc::setFlushFreq(500);
        }
        else{
            gbc::setFlushFreq(16);
        }
        gbc::setTimerFunc(flashFunc);
    }
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
void myResize(int width, int height){
    gbc::setViewPort2D(0, 640, 480, 0, 0, 0, 640, 480);
    glutReshapeWindow(640, 480);
}
#pragma clang diagnostic pop

void myKeyboard(unsigned char key, int x, int y){
    switch(key){
        case 27:{   // ESC key
            if(mode == POLYLINE && temppl.getConstPoints().size() >= 2){
                polylines.push(temppl);
            }
            if(mode == LOOPLINE && templl.getConstPoints().size() >= 3){
                looplines.push(templl);
            }
            temppl.getPoints().clear();
            templl.getPoints().clear();
            clip_point.set(-1, -1);
            mode = NORMAL;
            break;
        }
        case 'p':{
            myKeyboard(27, x, y);
            mode = POLYLINE;
            break;
        }
        case 'l':{
            myKeyboard(27, x, y);
            mode = LOOPLINE;
            break;
        }
        case 'm':{
            myKeyboard(27, x, y);
            mode = MOVE;
            break;
        }
        case 'd':{
            myKeyboard(27, x, y);
            mode = DELETE;
            break;
        }
        case 'r':{
            myKeyboard(27, x, y);
            mode = RECTCLIP;
            cliped_lines.getVector().clear();
            break;
        }
        case 'c':{
            if(looplines.size() >= 1 && mode != POLYGONCLIP){
                myKeyboard(27, x, y);
                mode = POLYGONCLIP;
                cliped_lines.getVector().clear();
                getClipedLines(looplines.get(looplines.size() - 1));
            }
            break;
        }
        case 'f':{
            if(looplines.size() >= 2 && mode != FLASH){
                myKeyboard(27, x, y);
                flash_start.assign(looplines.get(looplines.size() - 2));
                flash_end.assign(looplines.get(looplines.size() - 1));
                if(flash_start.size() < flash_end.size()){
                    flash_start.prepareTween(flash_end);
                }
                else if(flash_end.size() < flash_start.size()){
                    flash_end.prepareTween(flash_start);
                }
                flash_t = 0;
                gbc::setFlushFreq(16);
                gbc::setTimerFunc(flashFunc);
                mode = FLASH;
            }
            break;
        }
        case 'q':{
            exit(0);
        }
        default:
            break;
    }
}

void myDrag(int x, int y){
    if(moving_shape_type == 1){
        polylines.get(moving_shape_pos).get(moving_point_pos).set(x, y);
    }
    if(moving_shape_type == 2){
        looplines.get(moving_shape_pos).get(moving_point_pos).set(x, y);
    }
}

void myMouse(int button, int state, int x, int y){
#ifdef DEBUG
    std::cout << '(' << x << ',' << y << ')' << std::endl;
#endif
    if(mode == POLYLINE && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        temppl.addPoint(x, y);
    }
    if(mode == LOOPLINE && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        temppl.addPoint(x, y);
        templl.addPoint(x, y);
    }
    if(mode == DELETE && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        deletePoint(x, y);
    }
    if(mode == MOVE && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        std::vector<size_t> point_data = getNearPoint(x, y);
        if(point_data.at(0) != 0){
            moving_shape_type = point_data.at(0);
            moving_shape_pos = point_data.at(1);
            moving_point_pos = point_data.at(2);
            mode = MOVING;
            gbc::setMotionFunc(myDrag);
        }
    }
    if(mode == MOVING && button == GLUT_LEFT_BUTTON && state == GLUT_UP){
        mode = MOVE;
        gbc::setMotionFunc(NULL);
        moving_shape_type = 0;
    }
    if(mode == RECTCLIP && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if(clip_point.getX() == -1){    // first click
            clip_point.set(x, y);
        }
        else{   // second click
            if(x != clip_point.getX() && y != clip_point.getY()){
                cliped_lines.getVector().clear();
                clip_rect.setPoint(clip_point.getX(), clip_point.getY(), x, y);
                getClipedLines(clip_rect);
                clip_point.set(-1, -1);
            }
        }
    }
}

int main(int argc, char* argv[]){
    gbc::init(argc, argv);
    gbc::setWindowSize(640, 480);
    gbc::createWindow("paint");
    gbc::fillWindow(255, 255, 255);

    gbc::setDisplayFunc(myDisplay);
    gbc::setKeyboardFunc(myKeyboard);
    gbc::setMouseFunc(myMouse);
    gbc::setResizeFunc(myResize);

    gbc::showWindow();

    return 0;
}
