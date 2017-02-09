//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Curve2D.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Curve2D_h
#define Curve2D_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Curve.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Curve2D {

    public:

        Curve2D();
        void render(bool markers, bool animation);
        const Curve &x() const;
        const Curve &y() const;
        void read(const string &filename);
        void write(const string &filename) const;
        void add(double x, double y);
        void modify(double x, double y);
        void insert();
        void remove();
        void clear();
        void next();
        void previous();
        void first();
        void last();
        int i() const;
        int n() const;
        double t(int m) const;

    private:

        Curve _x;
        Curve _y;
        int _position;

    };

} // ComputerGraphics

#endif // Curve2D_h

//------------------------------------------------------------------------------
