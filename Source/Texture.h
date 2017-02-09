//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Texture.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Texture_h
#define Texture_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <GL/glut.h>

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Texture {

    public:

        Texture() :
            _texture(0),
            _mipmap(true),
            _replace(false) {
            _filename = "../Data/BUZZ.bmp";
        }
        ~Texture() {
            glDeleteTextures(1, &_texture);
        }
        void read();
        void render() const;

    private:

        Texture(const Texture &texture);
        Texture &operator=(const Texture &texture);
        virtual void write(ostream &out) const { cout << "Texture" << endl; }

        string _filename;
        GLuint _texture;
        bool _mipmap;
        bool _replace;

    };

} // ComputerGraphics

#endif // Texture_h

//------------------------------------------------------------------------------
