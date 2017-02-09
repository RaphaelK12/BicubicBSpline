//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Sphere.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Sphere_h
#define Sphere_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Curve3D.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Sphere {

    public:

        Sphere();
        void preset(Curve3D &curve3D);
        double x(double t);
        double y(double t);
        double z(double t);

    private:

        double _a;
        double _b;
        double _c;

    };

} // ComputerGraphics

#endif // Sphere_h

//------------------------------------------------------------------------------
