//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Patch3D.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Patch3D_h
#define Patch3D_h

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

    class Patch3D {

    public:

        Patch3D(int u, int v, int tiles);
        ~Patch3D();
        Patch3D(const Patch3D &patch3D);
        Patch3D &operator=(const Patch3D &patch3D);
        void tiles(int tiles);
        void modify();
        void render(Vectors **point, int m, int n, bool texture);
        void matrices(Vectors **point, int m, int n);
        void vertices();
        void normals();
        void write(ostream &out, int m, int n) const;

    private:

        void create();
        void erase();
        void copy(const Patch3D &patch3D);

        int _u;
        int _v;
        int _tiles;
        bool _valid;
        Vectors _matrix[ORDER][ORDER];
        Vectors **_vertex;
        Vectors **_normal;

    };

} // ComputerGraphics

#endif // Patch3D_h

//------------------------------------------------------------------------------
