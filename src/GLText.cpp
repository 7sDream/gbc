//
// Created by i7sdream on 15-10-3.
//

#include "GLText.h"

namespace gbc{
    GLText::GLText(const std::string& s, void* f)
        : string(s), font(f){
    }

    GLText::GLText(const GLText& s)
        : string(s.string), font(s.font){
    }

    void* GLText::getFont() const{
        return font;
    }

    const unsigned char* GLText::getString() const{
        return reinterpret_cast<const unsigned char*>(string.c_str());
    }

}