#include "GBC.h"

void myDisplay(){
    // Clean Screen.
    gbc::BlackPen.clear(255, 255, 255);
    
    // Draw point.
    gbc::BlackPen.setSize(10);
    gbc::BlackPen.draw(gbc::GLPoint(250, 250));
    
    // Draw line.
    gbc::BlackPen.setSize(1);
    gbc::BlackPen.draw(gbc::GLLine3D(250, 250, 0, 305, 290, 0));
    
    // Draw text.
    gbc::BlackPen.draw(gbc::GLText("Hello World!"), 320, 300);
    
    // Draw Rect.
    gbc::BlackPen.draw(gbc::GLRect(320-15, 300+20, 320+100, 300-10));
    
    // Flush buff to screen.
    gbc::BlackPen.flush();
}

int main(int argc, char *argv[]){
    // Init.
    gbc::init(argc, argv);
    // Set window size.
    gbc::setWindowSize(640, 480);
    // Set window title.
    gbc::createWindow("Hello world");
    // Set window background color.
    gbc::fillWindow(255, 255, 255);
    // Set coord to window map.
    gbc::setViewPort2D(0, 640, 0, 480, 0, 0, 640, 480);
    // Set the drawer function.
    gbc::setDisplayFunc(myDisplay);
    // Show window.
    gbc::showWindow();

    return 0;
}
