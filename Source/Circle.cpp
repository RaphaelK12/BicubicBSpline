//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Circle.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#pragma hdrstop
#include "Circle.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// constructor
Circle::Circle() : _a(0.0) {
}

//------------------------------------------------------------------------------
// preset
void Circle::preset(Curve2D &curve2d) {
    int i;
    // generate a polar coordinate curve
    _a = 0.5;
    const int N = 9;
    // generate a cubic curve
    curve2d.clear();
    for (i = 0; i < N; i++) {
        double t = -1.0 + 2.0 * (double)i / (double)(N - 1);
        curve2d.add(x(t), y(t));
    }
}

//------------------------------------------------------------------------------
// get x value
double Circle::x(double t) {
    return _a * cos(PI * t);
}

//------------------------------------------------------------------------------
// get y value
double Circle::y(double t) {
    return _a * sin(PI * t);
}

//------------------------------------------------------------------------------
