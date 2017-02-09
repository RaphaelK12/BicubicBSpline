//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Test.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Test_h
#define Test_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Curve1D.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Test {

    public:

        Test();
        void preset(Curve1D &curve1d, const string &filename);
        double y(double t);

    private:

        double _a;
        double _b;
        double _c;
        double _d;

    };

} // ComputerGraphics

#endif // Test_h

//------------------------------------------------------------------------------
