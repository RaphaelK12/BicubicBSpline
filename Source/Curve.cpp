//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Curve.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <GL/glut.h>
#pragma hdrstop
#include "Curve.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// constructor
Curve::Curve() : _n(0), _i(0), _size(1) {
    _f = new double[_size];
}

//------------------------------------------------------------------------------
// destructor
Curve::~Curve() {
    erase();
}

//------------------------------------------------------------------------------
// render data points
void Curve::render(bool markers) const {
    int point;
    glColor3d(0.0, 0.0, 1.0);
    glLineWidth(LINE_WIDTH);
    glDisable(GL_LINE_SMOOTH);
    glBegin(GL_LINE_STRIP);
        glColor3d(0.0, 0.0, 1.0);
        for (point = 0; point <= RESOLUTION; point++) {
            double tPlot = t(0) + (double)point / (double)RESOLUTION * (t(n() - 1) - t(0));
            glVertex2d(tPlot, vertex(tPlot));
        }
    glEnd();
    if (markers) {
        glPointSize(POINT_SIZE);
        glEnable(GL_POINT_SMOOTH);
        glBegin(GL_POINTS);
            glColor3d(0.0, 0.0 ,1.0);
            for (point = 0; point < n(); point++) {
                glVertex2d(t(point), f(point));
            }
            glColor3d(1.0, 0.0, 0.0);
            glVertex2d(t(i()), f(i()));
        glEnd();
    }
}

//------------------------------------------------------------------------------
// add data point
void Curve::add(double f) {
    _n++;
    resize();
    _f[n() - 1] = f;
}

//------------------------------------------------------------------------------
// modify data point
void Curve::modify(double f) {
    if (i() >= 0 && i() < n()) {
        _f[i()] += f;
    }
}

//------------------------------------------------------------------------------
// insert data point
void Curve::insert() {
    if (n() <= 0) {
        add(0.0);
    }
    else if (i() >= 0 && i() < n()) {
        double tInsert;
        double fInsert;
        if (i() < n() - 1) {
            tInsert = 0.5 * (t(i()) + t(i() + 1));
        }
        else if (i() == 0) {
            tInsert = t(i());
        }
        else {
            tInsert = t(i()) + (t(i()) - t(i() - 1));
        }
        fInsert = vertex(tInsert);
        _n++;
        resize();
        for (int point = n() - 1; point > i(); point--) {
            _f[point] = _f[point - 1];
        }
        _i++;
        _f[i()] = fInsert;
    }
    modify(0.0);
}

//------------------------------------------------------------------------------
// remove data point
void Curve::remove() {
    if (n() <= 1) {
        clear();
    }
    else if (i() >= 0 && i() < n()) {
        _n--;
        for (int point = i(); point < n(); point++) {
            _f[point] = _f[point + 1];
        }
        if (i() > 0) {
            _i--;
        }
    }
}

//------------------------------------------------------------------------------
// clear arrays
void Curve::clear() {
    _n = 0;
    _i = 0;
}

//------------------------------------------------------------------------------
// next data point
void Curve::next() {
    _i++;
    wrap();
}

//------------------------------------------------------------------------------
// previous data point
void Curve::previous() {
    _i--;
    wrap();
}

//------------------------------------------------------------------------------
// first data point
void Curve::first() {
    _i = 0;
}

//------------------------------------------------------------------------------
// last data point
void Curve::last() {
    _i = n() - 1;
}

//------------------------------------------------------------------------------
// wrap data point
void Curve::wrap() {
    if (i() < 0) {
        _i = n() - 1;
    }
    else if (_i > n() - 1) {
        _i = 0;
    }
}

//------------------------------------------------------------------------------
// get vertex
double Curve::vertex(double x) const {
    double point = 0.0;
    if (n() == 1) {
        point = f(0);
    }
    else {
        int i = 0;
        while ((t(i + 1) <= x) && (i + 1 < n() - 1)) {
            i++;
        }
        double dt = t(i + 1) - t(i);
        double s = (x - t(i)) / dt;
        double a[4][4] = {
            { -1.0,  3.0, -3.0, 1.0 },
            {  3.0, -6.0,  3.0, 0.0 },
            { -3.0,  0.0,  3.0, 0.0 },
            {  1.0,  4.0,  1.0, 0.0 }};
        for (int j = 0; j < 4; j++) {
            double b = a[0][j];
            for (int k = 1; k < 4; k++) {
                b = b * s + a[k][j];
            }
            point += b * f(i + j - 1);
        }
        point /= 6.0;
    }
    return point;
}

//------------------------------------------------------------------------------
// get data point
int Curve::i() const {
    return _i;
}

//------------------------------------------------------------------------------
// get number of data points
int Curve::n() const {
    return _n;
}

//------------------------------------------------------------------------------
// get data point parameter
double Curve::t(int m) const {
    double tValid;
    if (n() < 2) {
        tValid = -1.0;
    }
    else if (m < 0) {
        tValid = -1.0;
    }
    else if (m > n() - 1) {
        tValid = 1.0;
    }
    else {
        tValid = -1.0 + 2.0 * (double)m / (double)(n() - 1);
    }
    return tValid;
}

//------------------------------------------------------------------------------
// get data point parameter
double Curve::t() const {
    return t(i());
}

//------------------------------------------------------------------------------
// get data point value
double Curve::f(int m) const {
    if (n() == 0) {
        return 0.0;
    }
    else if (m < 0) {
        return _f[0];
    }
    else if (m > n() - 1) {
        return _f[n() - 1];
    }
    else {
        return _f[m];
    }
}

//------------------------------------------------------------------------------
// get data point value
double Curve::f() const {
    return f(i());
}

//------------------------------------------------------------------------------
// erase arrays
void Curve::erase() {
    delete[] _f;
}

//------------------------------------------------------------------------------
// resize arrays
void Curve::resize() {
    if (_n > _size) {
        double *_fOld = _f;
        _f = new double[_n];
        for (int i = 0; i < _size; i++) {
            _f[i] = _fOld[i];
        }
        _size = _n;
        delete[] _fOld;
    }
}

//------------------------------------------------------------------------------
