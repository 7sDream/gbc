//
// Created by i7sdream on 15-9-28.
//

#pragma once

#include <vector>
#include <GL/freeglut.h>

namespace gbc{
    template<typename T>
    class GLShapeArray{
    private:
        std::vector<T*> shapes;
    public:
        GLShapeArray();
        GLShapeArray(const std::vector<T> shapes_);
        GLShapeArray(T shapes_[], const typename std::vector<T*>::size_type length);
        void push(const T& shape);
        void insert(const typename std::vector<T*>::size_type i, const T& shape);
        const T& get(const typename std::vector<T*>::size_type i) const;
        T& get(const typename std::vector<T*>::size_type i);
        const std::vector<T*>& getConstVector() const;
        std::vector<T*>& getVector();
        typename std::vector<T*>::size_type size() const;
        GLenum style() const;
        void draw() const;
        void remove(typename std::vector<T*>::size_type pos);
        void clear();
    };
}
