//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Curve.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Curve_h
#define Curve_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Curve {

    public:

        Curve();
        ~Curve();
        void render(bool markers) const;
        void add(double f);
        void modify(double f);
        void insert();
        void remove();
        void clear();
        void next();
        void previous();
        void first();
        void last();
        void wrap();
        double vertex(double x) const;
        int i() const;
        int n() const;
        double t(int m) const;
        double t() const;
        double f(int m) const;
        double f() const;

    private:

        Curve(const Curve &curve);
        Curve &operator=(const Curve &curve);
        void erase();
        void resize();

        int _n;
        int _i;
        int _size;
        double *_f;

    };

} // ComputerGraphics

#endif // Curve_h

//------------------------------------------------------------------------------
