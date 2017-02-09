//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Curve1D.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Curve1D_h
#define Curve1D_h

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

    class Curve1D {

    public:

        Curve1D();
        void render(bool markers, bool animation);
        const Curve &x() const;
        void read(const string &filename);
        void write(const string &filename) const;
        void add(double x);
        void modify(double x);
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
        int _position;

    };

} // ComputerGraphics

#endif // Curve1D_h

//------------------------------------------------------------------------------
