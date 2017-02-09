//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Test.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#pragma hdrstop
#include "Test.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// constructor
Test::Test() : _a(0.0), _b(0.0), _c(0.0), _d(0.0) {
}

//------------------------------------------------------------------------------
// preset
void Test::preset(Curve1D &curve1d, const string &filename) {
    ofstream out(filename.c_str());
    if (!out.good()) {
        throw string("Error : Invalid file name = " + filename);
    }
    int i;
    // generate a cubic curve
    _a = 0.5;
    _b = -0.25;
    _c = 0.5;
    _d = 0.25;
    const int N = 11;
    curve1d.clear();
    for (i = 0; i < N; i++) {
        double t = -1.0 + 2.0 * (double)i / (double)(N - 1);
        curve1d.add(y(t));
    }
    // determine cubic values
    out << endl;
    out << "The cubic function was evaluated for " << N << " values of x" << endl;
    out << endl;
    out << "    y = (((((a * x) + b) * x) + c) * x) + d" << endl;
    out << endl;
    out << "    a = " << _a << endl;
    out << "    b = " << _b << endl;
    out << "    c = " << _c << endl;
    out << "    d = " << _d << endl;
    out << endl;
    // determine errors in B-spline values
    out << "The corresponding B-spline function was evaluated at the end points of each of its sections"
        << endl;
    out << "These values were compared with the relevant weighted sums of the cubic function" << endl;
    out << endl;
    out << "    y = (y0 + 4.0 * y1 + y2) / 6.0" << endl;
    out << "    y = (y1 + 4.0 * y2 + y3) / 6.0" << endl;
    out << endl;
    out << "The errors between the weighted sums and the B-spline function were evaluated" << endl;
    out << endl;
    double yError = 0.0;
    for (i = 0; i < N - 1; i++) {
        int i0 = i - 1;
        int i1 = i;
        int i2 = i + 1;
        int i3 = i + 2;
        i0 = (i0 < 0) ? 0 : ((i0 >= N - 1) ? N - 1 : i0);
        i1 = (i1 < 0) ? 0 : ((i1 >= N - 1) ? N - 1 : i1);
        i2 = (i2 < 0) ? 0 : ((i2 >= N - 1) ? N - 1 : i2);
        i3 = (i3 < 0) ? 0 : ((i3 >= N - 1) ? N - 1 : i3);
        double t0 = curve1d.t(i0);
        double t1 = curve1d.t(i1);
        double t2 = curve1d.t(i2);
        double t3 = curve1d.t(i3);
        double ySum0 = (y(t0) + 4.0 * y(t1) + y(t2)) / 6.0;
        double ySum1 = (y(t1) + 4.0 * y(t2) + y(t3)) / 6.0;
        double ySpline0 = curve1d.x().vertex(t1);
        double ySpline1 = curve1d.x().vertex(t2);
        double error;
        if ((error = fabs(ySum0 - ySpline0)) > yError) {
            yError = error;
        }
        if ((error = fabs(ySum1 - ySpline1)) > yError) {
            yError = error;
        }
        out << left << "    x = " << setw(5) << t1 << "    y = " << setw(10) << y(t1)
            << " weighted sum = " << setw(10) << ySum0 << " B-spline = " << setw(10) << ySpline0
            << " error = " << ySum0 - ySpline0 << endl;
        out << left << "    x = " << setw(5) << t2 << "    y = " << setw(10) << y(t2)
            << " weighted sum = " << setw(10) << ySum1 << " B-spline = " << setw(10) << ySpline1
            << " error = " << ySum1 - ySpline1 << endl;
    }
    out << endl;
    out << "The maximum absolute error was " << yError << endl;
    out << endl;
}

//------------------------------------------------------------------------------
// get y value
double Test::y(double t) {
    return (((_a * t) + _b) * t + _c) * t + _d;
}

//------------------------------------------------------------------------------
