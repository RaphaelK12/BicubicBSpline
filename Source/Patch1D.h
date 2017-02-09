//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Patch1D.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Patch1D_h
#define Patch1D_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Vectors.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Patch1D {

    public:

        Patch1D(int u = 0, int v = 0);
        void modify();
        void render(double **z, int m, int n);
        void matrix(double **z, int m, int n);
        void vertices();
        void normals();
        int u() { return _u; }
        int v() { return _v; }

    private:

        int _u;
        int _v;
        bool _valid;
        double _matrix[ORDER][ORDER];
        double _points[TILES + 1][TILES + 1];
        double _vertex[TILES + 1][TILES + 1];
        Vectors _normal[TILES + 1][TILES + 1];

    };

} // ComputerGraphics

#endif // Patch1D_h

//------------------------------------------------------------------------------
