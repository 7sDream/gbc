//
// Created by i7sdream on 15-11-29.
//

#pragma once

#include <fstream>
#include "GLLoopline2D.h"
#include "GLShapeArray.h"

namespace gbc{
    class MeshFile {
    private:
        GLShapeArray<GLLoopline2D> faces;
    public:
        MeshFile(std::ifstream& file);
        const GLShapeArray<GLLoopline2D>& getFaces() const;
    };
}
