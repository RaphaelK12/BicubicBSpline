//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Curve3D.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Curve3D_h
#define Curve3D_h

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

    class Curve3D {

    public:

        Curve3D();
        void render(bool markers, bool animation);
        const Curve &x() const;
        const Curve &y() const;
        const Curve &z() const;
        void read(const string &filename);
        void write(const string &filename) const;
        void add(double x, double y, double z);
        void modify(double x, double y, double z);
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
        void rotate(double x, double y, double z);
        void play();
        void spin();
        void stop();

    private:

        Curve _x;
        Curve _y;
        Curve _z;
        bool _spin;
        double _angleX;
        double _angleY;
        double _angleZ;
        bool _spinX;
        bool _spinY;
        bool _spinZ;
        int _position;

    };

} // ComputerGraphics

#endif // Curve3D_h

//------------------------------------------------------------------------------
