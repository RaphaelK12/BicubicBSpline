//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Circle.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Circle_h
#define Circle_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Curve2D.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Circle {

    public:

        Circle();
        void preset(Curve2D &curve2d);
        double x(double t);
        double y(double t);

    private:

        double _a;

    };

} // ComputerGraphics

#endif // Circle_h

//------------------------------------------------------------------------------
