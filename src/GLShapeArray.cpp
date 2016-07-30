//
// Created by i7sdream on 15-9-29.
//

#ifndef GBC_GLSHAPEARRAY_CPP
#define GBC_GLSHAPEARRAY_CPP

#include "GLShapeArray.h"

namespace gbc{
    template<typename T>
    GLShapeArray<T>::GLShapeArray(){
    }

    template<typename T>
    GLShapeArray<T>::GLShapeArray(const std::vector<T> shapes_){
        for(auto &i : shapes_){
            shapes.push_back(new T(i));
        }
    }

    template<typename T>
    GLShapeArray<T>::GLShapeArray(T shapes_[], const typename std::vector<T *>::size_type n){
        for(size_t i = 0; i < n; i++){
            shapes.push_back(new T(shapes_[i]));
        }
    }

    template<typename T>
    typename std::vector<T*>::size_type GLShapeArray<T>::size() const{
        return shapes.size();
    }

    template<typename T>
    GLenum GLShapeArray<T>::style() const{
        return shapes.front()->style();
    }

    template<typename T>
    void GLShapeArray<T>::draw() const{
        for(auto &i : shapes){
            i->draw();
        }
    }

    template<typename T>
    void GLShapeArray<T>::push(const T &shape){
        shapes.push_back(new T(shape));
    }

    template<typename T>
    void GLShapeArray<T>::insert(const typename std::vector<T *>::size_type i, const T &shape){
        shapes.insert(shapes.begin() + i, new T(shape));
    }

    template<typename T>
    const T& GLShapeArray<T>::get(const typename std::vector<T *>::size_type i) const{
        return *shapes.at(i);
    }

    template <typename T>
    T& GLShapeArray<T>::get(const typename std::vector<T *>::size_type i){
        return *shapes.at(i);
    }

    template<typename T>
    const std::vector<T *> &GLShapeArray<T>::getConstVector() const{
        return shapes;
    }

    template<typename T>
    std::vector<T *> &GLShapeArray<T>::getVector(){
        return shapes;
    }

    template <typename T>
    void GLShapeArray<T>::remove(typename std::vector<T *>::size_type pos){
        if(pos < size()){
            shapes.erase(shapes.begin() + pos);
        }
    }

    template <typename T>
    void GLShapeArray<T>::clear(){
        shapes.clear();
    }
}

#endif // ifndef GBC_GLSHAPEARRAY_CPP
