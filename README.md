# GBC - OpenGL and GLUT Based Classes

## 简介

这是一个基于 OpenGL 和 GLUT 的 C++ 类库，将 OpenGL 的绘图操作和 GLUT 提供的 GUI 相关操作整理成类，方便使用。

PS：这只是我在学习图形学课程时方便编写代码而写的一个工具库，对 3D 的支持还很不完善。

## 依赖

依赖 OpenGL，GLUT 以及 GLM 库。

在 Debian 系 Linux 上大概可通过 

```bash
sudo apt-get install freeglut3 freeglut3-dev libglm-dev
```

进行安装，其他发行版请自行搜索。

## 使用

```cpp
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
```

![](http://ww2.sinaimg.cn/large/88e401f0gw1f6bsmpwnorj20hs0e2glm.jpg)

更多例子可到 example 文件夹中查看。

## License

WTF.

