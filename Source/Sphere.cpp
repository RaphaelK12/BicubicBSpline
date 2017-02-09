//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Sphere.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#pragma hdrstop
#include "Sphere.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// constructor
Sphere::Sphere() : _a(0.0), _b(0.0), _c(0.0) {
}

//------------------------------------------------------------------------------
// preset
void Sphere::preset(Curve3D &curve3D) {
    int i;
    // generate a polar coordinate curve
    _a = 0.5;
    _b = 0.5;
    _c = 7.0;
    const int N = 61;
    // generate a cubic curve
    curve3D.clear();
    for (i = 0; i < N; i++) {
        double t = -1.0 + 2.0 * (double)i / (double)(N - 1);
        curve3D.add(x(t), y(t), z(t));
    }
}

//------------------------------------------------------------------------------
// get x value
double Sphere::x(double t) {
    return _a * cos(0.5 * PI * t) * cos(_c * PI * t);
}

//------------------------------------------------------------------------------
// get y value
double Sphere::y(double t) {
    return _a * cos(0.5 * PI * t) * sin(_c * PI * t);
}

//------------------------------------------------------------------------------
// get z value
double Sphere::z(double t) {
    return _b * sin(0.5 * PI * t);
}

//------------------------------------------------------------------------------
