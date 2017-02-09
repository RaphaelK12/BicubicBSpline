//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Curve3D.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <fstream>
#include <GL/glut.h>
#pragma hdrstop
#include "Curve3D.h"
#include "Curve.h"
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// constructor
Curve3D::Curve3D() : 
    _spin(true), 
    _angleX(0.0), 
    _angleY(0.0), 
    _angleZ(0.0), 
    _spinX(false), 
    _spinY(true), 
    _spinZ(false), 
    _position(0) {
}

//------------------------------------------------------------------------------
// render data points
void Curve3D::render(bool markers, bool animation) {
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    static double angle = 0.0;
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
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ',');
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'Z');
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ')');
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '(');
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'T');
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ')');
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
    glLineWidth(LINE_WIDTH);
    glDisable(GL_LINE_SMOOTH);
    glBegin(GL_LINE_STRIP);
        glColor3d(0.0, 0.0, 1.0);
        for (point = 0; point <= RESOLUTION; point++) {
            double tPoint = t(0) + (double)point / (double)RESOLUTION * (t(n() - 1) - t(0));
            glVertex3d(x().vertex(tPoint), y().vertex(tPoint), z().vertex(tPoint));
        }
    glEnd();
    if (markers) {
        glPointSize(POINT_SIZE);
        glEnable(GL_POINT_SMOOTH);
        glBegin(GL_POINTS);
            glColor3d(0.0, 0.0, 1.0);
            for (point = 0; point < n(); point++) {
                glVertex3d(x().f(point), y().f(point), z().f(point));
            }
            glColor3d(1.0, 0.0, 0.0);
            glVertex3d(x().f(x().i()), y().f(y().i()), z().f(y().i()));
        glEnd();
    }
    if (animation) {
        glPointSize(POINT_SIZE);
        glEnable(GL_POINT_SMOOTH);
        glBegin(GL_POINTS);
            glColor3d(1.0, 0.0, 1.0);
            double tPoint = t(0) + (double)_position / (double)RESOLUTION * (t(n() - 1) - t(0));
            glVertex3d(x().vertex(tPoint), y().vertex(tPoint), z().vertex(tPoint));
            _position = (_position + 1) % RESOLUTION;
        glEnd();
    }
    else {
        _position = 0;
    }
    glPopMatrix();
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
    // z window
    glViewport(0, 0, BORDER * width, BORDER * height);
    glColor3d(0.0, 0.0, 0.0);
    glRasterPos2d(-1.0, -1.0);
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'Z');
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '(');
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'T');
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, ')');
    glPushMatrix();
    glScaled(1.0, -1.0, 1.0);
    z().render(markers);
    glPopMatrix();
}

//------------------------------------------------------------------------------
// get x
const Curve &Curve3D::x() const {
    return _x;
}

//------------------------------------------------------------------------------
// get y
const Curve &Curve3D::y() const {
    return _y;
}

//------------------------------------------------------------------------------
// get z
const Curve &Curve3D::z() const {
    return _z;
}

//------------------------------------------------------------------------------
// read data points
void Curve3D::read(const string &filename) {
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
        double z;
        in >> x >> y >> z;
        add(x, y, z);
    }
}

//------------------------------------------------------------------------------
// write data points
void Curve3D::write(const string &filename) const {
    ofstream out(filename.c_str());
    if (!out.good()) {
        throw string("Error : Invalid file name = " + filename);
    }
    out << n() << endl;
    for (int i = 0; i < n(); i++) {
        out << _x.f(i) << " " << _y.f(i) << " " << _z.f(i) << endl;
    }
}

//------------------------------------------------------------------------------
// add data point
void Curve3D::add(double x, double y, double z) {
    _x.add(x);
    _y.add(y);
    _z.add(z);
}

//------------------------------------------------------------------------------
// modify data point
void Curve3D::modify(double x, double y, double z) {
    _x.modify(x);
    _y.modify(y);
    _z.modify(z);
}

//------------------------------------------------------------------------------
// insert data point
void Curve3D::insert() {
    _x.insert();
    _y.insert();
    _z.insert();
}

//------------------------------------------------------------------------------
// remove data point
void Curve3D::remove() {
    _x.remove();
    _y.remove();
    _z.remove();
}

//------------------------------------------------------------------------------
// clear arrays
void Curve3D::clear() {
    _x.clear();
    _y.clear();
    _z.clear();
}

//------------------------------------------------------------------------------
// next data point
void Curve3D::next() {
    _x.next();
    _y.next();
    _z.next();
}

//------------------------------------------------------------------------------
// previous data point
void Curve3D::previous() {
    _x.previous();
    _y.previous();
    _z.previous();
}

//------------------------------------------------------------------------------
// first data point
void Curve3D::first() {
    _x.first();
    _y.first();
    _z.first();
}

//------------------------------------------------------------------------------
// last data point
void Curve3D::last() {
    _x.last();
    _y.last();
    _z.last();
}

//------------------------------------------------------------------------------
// get index of data point
int Curve3D::i() const {
    return x().i();
}

//------------------------------------------------------------------------------
// get number of data points
int Curve3D::n() const {
    return x().n();
}

//------------------------------------------------------------------------------
// get data point parameter
double Curve3D::t(int m) const {
    return x().t(m);
}

//------------------------------------------------------------------------------
// rotate
void Curve3D::rotate(double x, double y, double z) {
    _angleX += x;
    _angleY += y;
    _angleZ += z;
}

//------------------------------------------------------------------------------
// play spin
void Curve3D::play() {
    _spin = !_spin;
}

//------------------------------------------------------------------------------
// set spin axis
void Curve3D::spin() {
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
void Curve3D::stop() {
    _spin = false;
    _angleX = 0.0;
    _angleY = 0.0;
    _angleZ = 0.0;
}

//------------------------------------------------------------------------------
