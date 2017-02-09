//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Surface1D.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Surface1D_h
#define Surface1D_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include "Patch1D.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Surface1D {

    public:

        Surface1D(int m = 2, int n = 2);
        ~Surface1D();
        Surface1D(const Surface1D &surface);
        Surface1D &operator=(const Surface1D &surface);
        void read(const string &filename);
        void write(const string &filename) const;
        void clear();
        void preset();
        void next(bool u, bool v);
        void previous(bool u, bool v);
        void first(bool u, bool v);
        void last(bool u, bool v);
        void modify(double z);
        void insert();
        void remove();
        void render(bool markers);
        void rotate(double x, double y, double z);
        void play();
        void spin();
        void stop();

    private:

        void create();
        void erase();
        void copy(const Surface1D &surface);
        void wrap();
        void clip();

        double **_z;
        Patch1D ***_patch;
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

    };

} // ComputerGraphics

#endif // Surface1D_h

//------------------------------------------------------------------------------
