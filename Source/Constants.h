//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Constants.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Constants_h
#define Constants_h

//------------------------------------------------------------------------------
// include files

#include <cmath>

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // constants

    const int WIDTH = 600;
    const int HEIGHT = 600;
    const int RESOLUTION = 500;
    const double EPSILON = 1.0e-6;
    const double INFINITY = 1.0e6;
    const double PI = acos(0.0) * 2.0;
    const double RAD_TO_DEG = 180.0 / PI;
    const double DEG_TO_RAD = PI / 180.0;
    const double LINE_WIDTH = 1.0;
    const double POINT_SIZE = 6.0;
    const int ORDER = 4;
    const int TILES = 16;

} // ComputerGraphics

#endif // Constants_h

//------------------------------------------------------------------------------
