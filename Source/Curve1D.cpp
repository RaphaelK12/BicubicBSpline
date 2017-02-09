//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Curve1D.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <fstream>
#include <GL/glut.h>
#pragma hdrstop
#include "Curve1D.h"
#include "Curve.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// constructor
Curve1D::Curve1D() : _position(0) {
}

//------------------------------------------------------------------------------
// render data points
void Curve1D::render(bool markers, bool animation) {
	glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    const double BORDER = 0.2;
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    int point;
    glViewport(0, 0, width, height);
    glBegin(GL_LINES);
        glColor3d(0.5, 0.5, 0.5);
        glVertex2d(-1.0 + BORDER * 2.0, -1.0);
        glVertex2d(-1.0 + BORDER * 2.0, 1.0);
        glVertex2d(-1.0, -1.0 + BORDER * 2.0);
        glVertex2d(1.0, -1.0 + BORDER * 2.0);
    glEnd();
    // main window
    glViewport(BORDER * width, BORDER * height, (1.0 - BORDER) * width, (1.0 - BORDER) * height);
    glColor3d(0.0, 0.0, 0.0);
    glRasterPos2d(-1.0, -1.0);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '(');
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'Y');
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ')');
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '(');
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'T');
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ')');
    glLineWidth(LINE_WIDTH);
    glDisable(GL_LINE_SMOOTH);
    glBegin(GL_LINE_STRIP);
        glColor3d(0.0, 0.0, 1.0);
        for (point = 0; point <= RESOLUTION; point++) {
            double tPoint = t(0) + (double)point / (double)RESOLUTION * (t(n() - 1) - t(0));
            glVertex2d(tPoint, x().vertex(tPoint));
        }
    glEnd();
    if (markers) {
        glPointSize(POINT_SIZE);
        glEnable(GL_POINT_SMOOTH);
        glBegin(GL_POINTS);
            glColor3d(0.0, 0.0, 1.0);
            for (point = 0; point < n(); point++) {
                glVertex2d(x().t(point), x().f(point));
            }
            glColor3d(1.0, 0.0, 0.0);
            glVertex2d(x().t(x().i()), x().f(x().i()));
        glEnd();
    }
    if (animation) {
        glPointSize(POINT_SIZE);
        glEnable(GL_POINT_SMOOTH);
        glBegin(GL_POINTS);
            glColor3d(1.0, 0.0, 1.0);
            double tPoint = t(0) + (double)_position / (double)RESOLUTION * (t(n() - 1) - t(0));
            glVertex2d(tPoint, x().vertex(tPoint));
            _position = (_position + 1) % RESOLUTION;
        glEnd();
    }
    else {
        _position = 0;
    }
    // y window
    glViewport(0, BORDER * height, BORDER * width, (1.0 - BORDER) * height);
    glColor3d(0.0, 0.0, 0.0);
    glRasterPos2d(-1.0, -1.0);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'Y');
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '(');
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'T');
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ')');
    x().render(markers);
}

//------------------------------------------------------------------------------
// get x
const Curve &Curve1D::x() const {
    return _x;
}

//------------------------------------------------------------------------------
// read data points
void Curve1D::read(const string &filename) {
    ifstream in(filename.c_str());
    if (!in.good()) {
        throw string("Error : Invalid file name = " + filename);
    }
    clear();
    int n;
    in >> n;
    for (int i = 0; i < n; i++) {
        double x;
        in >> x;
        add(x);
    }
}

//------------------------------------------------------------------------------
// write data points
void Curve1D::write(const string &filename) const {
    ofstream out(filename.c_str());
    if (!out.good()) {
        throw string("Error : Invalid file name = " + filename);
    }
    out << n() << endl;
    for (int i = 0; i < n(); i++) {
        out << _x.f(i) << endl;
    }
}

//------------------------------------------------------------------------------
// add data point
void Curve1D::add(double x) {
    _x.add(x);
}

//------------------------------------------------------------------------------
// modify data point
void Curve1D::modify(double x) {
    _x.modify(x);
}

//------------------------------------------------------------------------------
// insert data point
void Curve1D::insert() {
    _x.insert();
}

//------------------------------------------------------------------------------
// remove data point
void Curve1D::remove() {
    _x.remove();
}

//------------------------------------------------------------------------------
// clear arrays
void Curve1D::clear() {
    _x.clear();
}

//------------------------------------------------------------------------------
// next data point
void Curve1D::next() {
    _x.next();
}

//------------------------------------------------------------------------------
// previous data point
void Curve1D::previous() {
    _x.previous();
}

//------------------------------------------------------------------------------
// first data point
void Curve1D::first() {
    _x.first();
}

//------------------------------------------------------------------------------
// last data point
void Curve1D::last() {
    _x.last();
}

//------------------------------------------------------------------------------
// get index of data point
int Curve1D::i() const {
    return x().i();
}

//------------------------------------------------------------------------------
// get number of data points
int Curve1D::n() const {
    return x().n();
}

//------------------------------------------------------------------------------
// get data point parameter
double Curve1D::t(int m) const {
    return x().t(m);
}

//------------------------------------------------------------------------------
