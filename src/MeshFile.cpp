//
// Created by i7sdream on 15-11-29.
//

#include <string>
#include <iostream>
#include "MeshFile.h"

namespace gbc{
    MeshFile::MeshFile(std::ifstream& file) {
        GLShapeArray<GLPoint> points;
        int point_num, face_num, normal_num;
        file >> point_num >> normal_num >> face_num;
        for(int i = 0; i < point_num; i++){
            double x, y, z;
            file >> x >> y >> z;
            points.push(GLPoint(x, y, z));
        }
        // skip a \r\n
        file.get();
        // skip normal
        for(int i = 0; i < normal_num; i++){
            std::string str;
            std::getline(file, str);
        }
        for(int i = 0; i < face_num; i++){
            int num;
            file >> num;
            GLLoopline2D shape;
            for(int j = 0; j < num; j ++){
                int index;
                file >> index;
                shape.addPoint(points.get(index));
            }
            // skip normal index
            for(int j = 0; j < num; j++){
                int index;
                file >> index;
            }
            faces.push(shape);
        }
    }

    const GLShapeArray<GLLoopline2D>& MeshFile::getFaces() const{
        return faces;
    }
}