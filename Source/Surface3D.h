//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Surface3D.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Surface3D_h
#define Surface3D_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Patch3D.h"
#include "Texture.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Surface3D {

    public:

        Surface3D(int m = 2, int n = 2);
        ~Surface3D();
        Surface3D(const Surface3D &surface3D);
        Surface3D &operator=(const Surface3D &surface3D);
        void read(const string &filename);
        void write(const string &filename) const;
        void clear();
        void preset();
        void next(bool u, bool v);
        void previous(bool u, bool v);
        void first(bool u, bool v);
        void last(bool u, bool v);
        void modify(double x, double y, double z);
        void insert();
        void remove();
        void render(bool markers, bool wireframe, bool hull, bool solid, bool axes, bool texture);
        void rotate(double x, double y, double z);
        void play();
        void spin();
        void stop();
        void doubleTiles();
        void halfTiles();
        void texture();
        void mesh(const string &filename) const;

    private:

        void create();
        void erase();
        void copy(const Surface3D &surface3D);
        void wrap();
        void clip();

        Vectors **_point;
        Patch3D ***_patch;
        int _m;
        int _n;
        int _u;
        int _v;
        bool _spin;
        double _angleX;
        double _angleY;
        double _angleZ;
        bool _spinX;
        bool _spinY;
        bool _spinZ;
        int _tiles;
        Texture _texture;

    };

} // ComputerGraphics

#endif // Surface3D_h

//------------------------------------------------------------------------------
