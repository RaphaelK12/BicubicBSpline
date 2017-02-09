//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Control.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Control_h
#define Control_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <GL/glut.h>
#include "Curve1D.h"
#include "Curve2D.h"
#include "Curve3D.h"
#include "Test.h"
#include "Circle.h"
#include "Sphere.h"
#include "Surface1D.h"
#include "Surface3D.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // constants

    const int CURVE_1D = 0;
    const int CURVE_2D = 1;
    const int CURVE_3D = 2;
    const int SURFACE_1D = 3;
    const int SURFACE_2D = 4;
    const int SURFACE_3D = 5;

    //------------------------------------------------------------------------------
    // class definition

    class Control {

    public:

        Control() : 
            _surface1D(4, 4), 
            _surface3D(4, 4), 
            _motionX(0), 
            _motionY(0), 
            _dimension(CURVE_1D), 
            _markers(true), 
            _animation(true), 
            _axis(false), 
            _rotate(false), 
            _wireframe(false),
            _hull(true),
            _solid(true),
            _axes(true),
            _texture(false) {
        }
        ~Control() { cout << "Control object destructed" << endl; }
        void init(int argc, char **argv);
        void display();
        void reshape(int width, int height);
        void keyboard(unsigned char key, int x, int y);
        void special(int key, int x, int y);
        void mouse(int button, int state, int x, int y);
        void motion(int x, int y);
        void idle();

    private:

        Curve1D _curve1D;
        Curve2D _curve2D;
        Curve3D _curve3D;
        Test _test;
        Circle _circle;
        Sphere _sphere;
        Surface1D _surface1D;
        Surface3D _surface3D;
        int _motionX;
        int _motionY;
        int _dimension;
        bool _markers;
        bool _animation;
        bool _axis;
        bool _rotate;
        bool _wireframe;
        bool _hull;
        bool _solid;
        bool _axes;
        bool _texture;

    };

} // ComputerGraphics

#endif // Control_h

//------------------------------------------------------------------------------
