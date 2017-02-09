//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Texture.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <GL/glut.h>
#pragma hdrstop
#include "Texture.h"
#include "Bitmap.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// read texture
void Texture::read() {
    glGenTextures(1, &_texture);
    glBindTexture(GL_TEXTURE_2D, _texture);
    if (!glIsTexture(_texture)) {
		throw string("Error : Failed texture creation");
	}
    Bitmap bitmap;
    bitmap.read(const_cast<char *>(_filename.c_str()));
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmap.width(), bitmap.height(), 0, 
        GL_RGB, GL_UNSIGNED_BYTE, bitmap.image());
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bitmap.width(), bitmap.height(), 
        GL_RGB, GL_UNSIGNED_BYTE, bitmap.image());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (_mipmap) {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }
    else {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
}

//------------------------------------------------------------------------------
// render texture
void Texture::render() const {
    glBindTexture(GL_TEXTURE_2D, _texture);
    if (_replace) {
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    }
    else {
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    }
}

//------------------------------------------------------------------------------
