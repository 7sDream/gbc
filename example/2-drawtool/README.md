# Example - 绘图工具

## 编译

```bash
mkdir build
cd build
cmake ..
make
```

## 运行

```bash
./2_drawtool
```

## 使用

左上角标志当前模式。

P：画折线
L：画自动封闭线（再按一次 L 自动封闭）
M：拖动鼠标可移动拐点
D：点击拐点删除
R：矩形 CLIP，在矩形内的线段变成红色
C：用最后一次画的封闭线 CLIP （必须是凸多边形）
F：强制刷新
Q：退出

## 截图

![](http://ww2.sinaimg.cn/large/88e401f0gw1f6bt6uzojbg20hs0e3gok.gif)

