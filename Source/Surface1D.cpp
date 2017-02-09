//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Surface1D.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <fstream>
#include <GL/glut.h>
#pragma hdrstop
#include "Surface1D.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// constructor
Surface1D::Surface1D(int m /*= 2*/, int n /*= 2*/) :
    _m(m),
    _n(n),
    _u(0),
    _v(0),
    _spin(false),
    _angleX(0.0),
    _angleY(0.0),
    _angleZ(0.0),
    _spinX(false),
    _spinY(true),
    _spinZ(false) {
    create();
}

//------------------------------------------------------------------------------
// destructor
Surface1D::~Surface1D() {
    erase();
}

//------------------------------------------------------------------------------
// copy constructor
Surface1D::Surface1D(const Surface1D &surface1D) {
    copy(surface1D);
}

//------------------------------------------------------------------------------
// assignment operator
Surface1D &Surface1D::operator=(const Surface1D &surface1D) {
    if (this != &surface1D) {
        erase();
        copy(surface1D);
    }
    return *this;
}

//------------------------------------------------------------------------------
// create
void Surface1D::create() {
    _z = new double *[_n];
    for (int zV = 0; zV < _n; zV++) {
        _z[zV] = new double[_m];
        for (int zU = 0; zU < _m; zU++) {
            _z[zV][zU] = 0.0;
        }
    }
    _patch = new Patch1D **[_n - 1];
    for (int patchV = 0; patchV < _n - 1; patchV++) {
        _patch[patchV] = new Patch1D *[_m - 1];
        for (int patchU = 0; patchU < _m - 1; patchU++) {
            _patch[patchV][patchU] = new Patch1D(patchU, patchV);
        }
    }
}

//------------------------------------------------------------------------------
// erase
void Surface1D::erase() {
    for (int zV = 0; zV < _n; zV++) {
        delete[] _z[zV];
    }
    delete[] _z;
    for (int patchV = 0; patchV < _n - 1; patchV++) {
        for (int patchU = 0; patchU < _m - 1; patchU++) {
            delete _patch[patchV][patchU];
        }
        delete[] _patch[patchV];
    }
    delete[] _patch;
}

//------------------------------------------------------------------------------
// copy
void Surface1D::copy(const Surface1D &surface1D) {
    _m = surface1D._m;
    _n = surface1D._n;
    _u = surface1D._u;
    _v = surface1D._v;
    create();
    for (int zV = 0; zV < _n; zV++) {
        for (int zU = 0; zU < _m; zU++) {
            _z[zV][zU] = surface1D._z[zV][zU];
        }
    }
    for (int patchV = 0; patchV < _n - 1; patchV++) {
        for (int patchU = 0; patchU < _m - 1; patchU++) {
            *_patch[patchV][patchU] = *surface1D._patch[patchV][patchU];
        }
    }
}

//------------------------------------------------------------------------------
// read
void Surface1D::read(const string &filename) {
    ifstream in(filename.c_str());
    if (!in.good()) {
        throw string("Error : Invalid file name = " + filename);
    }
    erase();
    in >> _m;
    in >> _n;
    clip();
    create();
    for (int v = 0; v < _n; v++) {
        for (int u = 0; u < _m; u++) {
            in >> _z[v][u];
        }
    }
}

//------------------------------------------------------------------------------
// write
void Surface1D::write(const string &filename) const {
    ofstream out(filename.c_str());
    if (!out.good()) {
        throw string("Error : Invalid file name = " + filename);
    }
    out << _m << endl;
    out << _n << endl;
    for (int v = 0; v < _n; v++) {
        for (int u = 0; u < _m; u++) {
            out << _z[v][u] << endl;
        }
    }
}

//------------------------------------------------------------------------------
// clear
void Surface1D::clear() {
    erase();
    _m = 2;
    _n = 2;
    clip();
    create();
}

//------------------------------------------------------------------------------
// preset
void Surface1D::preset() {
    erase();
    _m = 4;
    _n = 4;
    clip();
    create();
}

//------------------------------------------------------------------------------
// next coordinate
void Surface1D::next(bool u, bool v) {
    if (u) {
        _u++;
    }
    if (v) {
        _v++;
    }
    wrap();
}

//------------------------------------------------------------------------------
// previous coordinate
void Surface1D::previous(bool u, bool v) {
    if (u) {
        _u--;
    }
    if (v) {
        _v--;
    }
    wrap();
}

//------------------------------------------------------------------------------
// first coordinate
void Surface1D::first(bool u, bool v) {
    if (u) {
        _u = 0;
    }
    if (v) {
        _v = 0;
    }
}

//------------------------------------------------------------------------------
// last coordinate
void Surface1D::last(bool u, bool v) {
    if (u) {
        _u = _m - 1;
    }
    if (v) {
        _v = _n - 1;
    }
}

//------------------------------------------------------------------------------
// wrap coordinates
void Surface1D::wrap() {
    if (_u < 0) {
        _u = _m - 1;
    }
    else if (_u > _m - 1) {
        _u = 0;
    }
    if (_v < 0) {
        _v = _n - 1;
    }
    else if (_v > _n - 1) {
        _v = 0;
    }
}

//------------------------------------------------------------------------------
// clip coordinates
void Surface1D::clip() {
    if (_u < 0) {
        _u = 0;
    }
    else if (_u > _m - 1) {
        _u = _m - 1;
    }
    if (_v < 0) {
        _v = 0;
    }
    else if (_v > _n - 1) {
        _v = _n - 1;
    }
}

//------------------------------------------------------------------------------
// modify
void Surface1D::modify(double z) {
    _z[_v][_u] += z;
    for (int patchV = _v - 2; patchV < _v + 2; patchV++) {
        if (patchV >= 0 && patchV < _n - 1) {
            for (int patchU = _u - 2; patchU < _u + 2; patchU++) {
                if (patchU >= 0 && patchU < _m - 1) {
                    _patch[patchV][patchU]->modify();
                }
            }
        }
    }
}

//------------------------------------------------------------------------------
// insert
void Surface1D::insert() {
    int u;
    int v;
    // copy old z
    int nOld = _n;
    double **zOld = _z;
    for (v = 0; v < _n; v++) {
        zOld[v] = _z[v];
        for (u = 0; u < _m; u++) {
            zOld[v][u] = _z[v][u];
        }
    }
    for (v = 0; v < _n - 1; v++) {
        for (u = 0; u < _m - 1; u++) {
            delete _patch[v][u];
        }
        delete[] _patch[v];
    }
    delete[] _patch;
    _m++;
    _n++;
    // create new z
    _z = new double *[_n];
    for (v = 0; v < _n; v++) {
        _z[v] = new double[_m];
        for (int u = 0; u < _m; u++) {
            if (v <= _v) {
                if (u <= _u) {
                    _z[v][u] = zOld[v][u];
                }
                else {
                    _z[v][u] = zOld[v][u - 1];
                }
            }
            else {
                if (u <= _u) {
                    _z[v][u] = zOld[v - 1][u];
                }
                else {
                    _z[v][u] = zOld[v - 1][u - 1];
                }
            }
        }
    }
    _patch = new Patch1D **[_n - 1];
    for (v = 0; v < _n - 1; v++) {
        _patch[v] = new Patch1D *[_m - 1];
        for (u = 0; u < _m - 1; u++) {
            _patch[v][u] = new Patch1D(u, v);
        }
    }
    // erase old z
    for (v = 0; v < nOld; v++) {
        delete[] zOld[v];
    }
    delete[] zOld;
}

//------------------------------------------------------------------------------
// remove
void Surface1D::remove() {
    if (_u > 0 && _u < _m - 1 && _v > 0 && _v < _n - 1 && _m > 2 && _n > 2) {
        int u;
        int v;
        // copy old z
        int nOld = _n;
        double **zOld = _z;
        for (v = 0; v < _n; v++) {
            zOld[v] = _z[v];
            for (u = 0; u < _m; u++) {
                zOld[v][u] = _z[v][u];
            }
        }
        for (v = 0; v < _n - 1; v++) {
            for (u = 0; u < _m - 1; u++) {
                delete _patch[v][u];
            }
            delete[] _patch[v];
        }
        delete[] _patch;
        _m--;
        _n--;
        // create new z
        _z = new double *[_n];
        for (v = 0; v < _n; v++) {
            _z[v] = new double[_m];
            for (int u = 0; u < _m; u++) {
                if (v < _v) {
                    if (u < _u) {
                        _z[v][u] = zOld[v][u];
                    }
                    else {
                        _z[v][u] = zOld[v][u + 1];
                    }
                }
                else {
                    if (u < _u) {
                        _z[v][u] = zOld[v + 1][u];
                    }
                    else {
                        _z[v][u] = zOld[v + 1][u + 1];
                    }
                }
            }
        }
        _patch = new Patch1D **[_n - 1];
        for (v = 0; v < _n - 1; v++) {
            _patch[v] = new Patch1D *[_m - 1];
            for (u = 0; u < _m - 1; u++) {
                _patch[v][u] = new Patch1D(u, v);
            }
        }
        // erase old z
        for (v = 0; v < nOld; v++) {
            delete[] zOld[v];
        }
        delete[] zOld;
    }
}

//------------------------------------------------------------------------------
// render
void Surface1D::render(bool markers) {
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    glViewport(0, 0, width, height);
    glPushMatrix();
    glRotated(_angleZ, 0.0, 0.0, 1.0);
    glRotated(_angleX, 1.0, 0.0, 0.0);
    glRotated(_angleY, 0.0, 1.0, 0.0);
    const double INCREMENT = 1.0;
    if (_spin && _spinX) {
        _angleX += INCREMENT;
    }
    if (_spin && _spinY) {
        _angleY += INCREMENT;
    }
    if (_spin && _spinZ) {
        _angleZ += INCREMENT;
    }
    if (markers) {
        // highlight control points
        GLfloat ambient[] = { 1.0, 1.0, 0.0, 1.0 };
        GLfloat diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
        GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat shininess = 10.0;
        GLfloat emission[] = { 0.0, 0.0, 0.0, 0.0 };
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
        for (int zV = 0; zV < _n; zV++) {
            for (int zU = 0; zU < _m; zU++) {
                glPushMatrix();
                glTranslated((double)zU / (double)(_m - 1) - 0.5,
                    (double)zV / (double)(_n - 1) - 0.5, _z[zV][zU]);
                GLUquadricObj *sphere = gluNewQuadric();
                gluQuadricDrawStyle(sphere, GLU_FILL);
                gluQuadricNormals(sphere, GLU_SMOOTH);
                gluSphere(sphere, 0.01, 20, 10);
                gluDeleteQuadric(sphere);
                glPopMatrix();
            }
        }
        // highlight current control point
        GLfloat ambient1[] = { 0.0, 1.0, 1.0, 1.0 };
        GLfloat diffuse1[] = { 0.0, 1.0, 1.0, 1.0 };
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
        glPushMatrix();
        glTranslated((double)_u / (double)(_m - 1) - 0.5,
            (double)_v / (double)(_n - 1) - 0.5, _z[_v][_u]);
        GLUquadricObj *sphere1 = gluNewQuadric();
        gluQuadricDrawStyle(sphere1, GLU_FILL);
        gluQuadricNormals(sphere1, GLU_SMOOTH);
        gluSphere(sphere1, 0.02, 20, 10);
        gluDeleteQuadric(sphere1);
        glPopMatrix();
    }
    for (int patchV = 0; patchV < _n - 1; patchV++) {
        for (int patchU = 0; patchU < _m - 1; patchU++) {
            _patch[patchV][patchU]->render(_z, _m, _n);
        }
    }
    glPopMatrix();
}

//------------------------------------------------------------------------------
// rotate
void Surface1D::rotate(double x, double y, double z) {
    _angleX += x;
    _angleY += y;
    _angleZ += z;
}

//------------------------------------------------------------------------------
// play spin
void Surface1D::play() {
    _spin = !_spin;
}

//------------------------------------------------------------------------------
// set spin axis
void Surface1D::spin() {
    if (_spinX) {
        _spinX = false;
        _spinY = true;
        _spinZ = false;
    }
    else if (_spinY) {
        _spinX = false;
        _spinY = false;
        _spinZ = true;
    }
    else if (_spinZ) {
        _spinX = true;
        _spinY = false;
        _spinZ = false;
    }
}

//------------------------------------------------------------------------------
// stop spin
void Surface1D::stop() {
    _spin = false;
    _angleX = 0.0;
    _angleY = 0.0;
    _angleZ = 0.0;
}

//------------------------------------------------------------------------------
