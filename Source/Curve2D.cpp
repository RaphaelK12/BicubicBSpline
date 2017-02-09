//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Curve2D.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <fstream>
#include <GL/glut.h>
#pragma hdrstop
#include "Curve2D.h"
#include "Curve.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// constructor
Curve2D::Curve2D() : _position(0) {
}

//------------------------------------------------------------------------------
// render data points
void Curve2D::render(bool markers, bool animation) {
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
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'X');
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ',');
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
            glVertex2d(x().vertex(tPoint), y().vertex(tPoint));
        }
    glEnd();
    if (markers) {
        glPointSize(POINT_SIZE);
        glEnable(GL_POINT_SMOOTH);
        glBegin(GL_POINTS);
            glColor3d(0.0, 0.0, 1.0);
            for (point = 0; point < n(); point++) {
                glVertex2d(x().f(point), y().f(point));
            }
            glColor3d(1.0, 0.0, 0.0);
            glVertex2d(x().f(x().i()), y().f(y().i()));
        glEnd();
    }
    if (animation) {
        glPointSize(POINT_SIZE);
        glEnable(GL_POINT_SMOOTH);
        glBegin(GL_POINTS);
            glColor3d(1.0, 0.0, 1.0);
            double tPoint = t(0) + (double)_position / (double)RESOLUTION * (t(n() - 1) - t(0));
            glVertex2d(x().vertex(tPoint), y().vertex(tPoint));
            _position = (_position + 1) % RESOLUTION;
        glEnd();
    }
    else {
        _position = 0;
    }
    // x window
    glViewport(BORDER * width, 0, (1.0 - BORDER) * width, BORDER * height);
    glColor3d(0.0, 0.0, 0.0);
    glRasterPos2d(-1.0, -1.0);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'X');
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '(');
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'T');
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ')');
    glPushMatrix();
    glScaled(-1.0, 1.0, 1.0);
    glRotated(90.0, 0.0, 0.0, 1.0);
    x().render(markers);
    glPopMatrix();
    // y window
    glViewport(0, BORDER * height, BORDER * width, (1.0 - BORDER) * height);
    glColor3d(0.0, 0.0, 0.0);
    glRasterPos2d(-1.0, -1.0);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'Y');
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '(');
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'T');
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ')');
    y().render(markers);
}

//------------------------------------------------------------------------------
// get x
const Curve &Curve2D::x() const {
    return _x;
}

//------------------------------------------------------------------------------
// get y
const Curve &Curve2D::y() const {
    return _y;
}

//------------------------------------------------------------------------------
// read data points
void Curve2D::read(const string &filename) {
    ifstream in(filename.c_str());
    if (!in.good()) {
        throw string("Error : Invalid file name = " + filename);
    }
    clear();
    int n;
    in >> n;
    for (int i = 0; i < n; i++) {
        double x;
        double y;
        in >> x >> y;
        add(x, y);
    }
}

//------------------------------------------------------------------------------
// write data points
void Curve2D::write(const string &filename) const {
    ofstream out(filename.c_str());
    if (!out.good()) {
        throw string("Error : Invalid file name = " + filename);
    }
    out << n() << endl;
    for (int i = 0; i < n(); i++) {
        out << _x.f(i) << " " << _y.f(i) << endl;
    }
}

//------------------------------------------------------------------------------
// add data point
void Curve2D::add(double x, double y) {
    _x.add(x);
    _y.add(y);
}

//------------------------------------------------------------------------------
// modify data point
void Curve2D::modify(double x, double y) {
    _x.modify(x);
    _y.modify(y);
}

//------------------------------------------------------------------------------
// insert data point
void Curve2D::insert() {
    _x.insert();
    _y.insert();
}

//------------------------------------------------------------------------------
// remove data point
void Curve2D::remove() {
    _x.remove();
    _y.remove();
}

//------------------------------------------------------------------------------
// clear arrays
void Curve2D::clear() {
    _x.clear();
    _y.clear();
}

//------------------------------------------------------------------------------
// next data point
void Curve2D::next() {
    _x.next();
    _y.next();
}

//------------------------------------------------------------------------------
// previous data point
void Curve2D::previous() {
    _x.previous();
    _y.previous();
}

//------------------------------------------------------------------------------
// first data point
void Curve2D::first() {
    _x.first();
    _y.first();
}

//------------------------------------------------------------------------------
// last data point
void Curve2D::last() {
    _x.last();
    _y.last();
}

//------------------------------------------------------------------------------
// get index of data point
int Curve2D::i() const {
    return x().i();
}

//------------------------------------------------------------------------------
// get number of data points
int Curve2D::n() const {
    return x().n();
}

//------------------------------------------------------------------------------
// get data point parameter
double Curve2D::t(int m) const {
    return x().t(m);
}

//------------------------------------------------------------------------------
