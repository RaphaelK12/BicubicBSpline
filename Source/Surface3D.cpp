//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Surface3D.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <fstream>
//#include <iomanip>
#include <GL/glut.h>
#pragma hdrstop
#include "Surface3D.h"
#include "Patch3D.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// constructor
Surface3D::Surface3D(int m /*= 2*/, int n /*= 2*/) :
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
    _spinZ(false),
    _tiles(16) {
    create();
}

//------------------------------------------------------------------------------
// destructor
Surface3D::~Surface3D() {
    erase();
}

//------------------------------------------------------------------------------
// copy constructor
Surface3D::Surface3D(const Surface3D &surface3D) {
    copy(surface3D);
}

//------------------------------------------------------------------------------
// assignment operator
Surface3D &Surface3D::operator=(const Surface3D &surface3D) {
    if (this != &surface3D) {
        erase();
        copy(surface3D);
    }
    return *this;
}

//------------------------------------------------------------------------------
// create
void Surface3D::create() {
    int u;
    int v;
    _point = new Vectors *[_n];
    for (v = 0; v < _n; v++) {
        _point[v] = new Vectors[_m];
        for (u = 0; u < _m; u++) {
            _point[v][u] = Vectors((double)u / (double)(_m - 1) - 0.5,
                (double)v / (double)(_n - 1) - 0.5, 0.0);
        }
    }
    _patch = new Patch3D **[_n - 1];
    for (v = 0; v < _n - 1; v++) {
        _patch[v] = new Patch3D *[_m - 1];
        for (u = 0; u < _m - 1; u++) {
            _patch[v][u] = new Patch3D(u, v, _tiles);
        }
    }
}

//------------------------------------------------------------------------------
// erase
void Surface3D::erase() {
    int u;
    int v;
    for (v = 0; v < _n; v++) {
        delete[] _point[v];
    }
    delete[] _point;
    for (v = 0; v < _n - 1; v++) {
        for (u = 0; u < _m - 1; u++) {
            delete _patch[v][u];
        }
        delete[] _patch[v];
    }
    delete[] _patch;
}

//------------------------------------------------------------------------------
// copy
void Surface3D::copy(const Surface3D &surface3D) {
    _m = surface3D._m;
    _n = surface3D._n;
    _u = surface3D._u;
    _v = surface3D._v;
    create();
    int u;
    int v;
    for (v = 0; v < _n; v++) {
        for (u = 0; u < _m; u++) {
            _point[v][u] = surface3D._point[v][u];
        }
    }
    for (v = 0; v < _n - 1; v++) {
        for (u = 0; u < _m - 1; u++) {
            *_patch[v][u] = *surface3D._patch[v][u];
        }
    }
}

//------------------------------------------------------------------------------
// read
void Surface3D::read(const string &filename) {
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
            double x;
            double y;
            double z;
            in >> x >> y >> z;
            _point[v][u].x(x);
            _point[v][u].y(y);
            _point[v][u].z(z);
        }
    }
}

//------------------------------------------------------------------------------
// write
void Surface3D::write(const string &filename) const {
    ofstream out(filename.c_str());
    if (!out.good()) {
        throw string("Error : Invalid file name = " + filename);
    }
    out << _m << endl;
    out << _n << endl;
    for (int v = 0; v < _n; v++) {
        for (int u = 0; u < _m; u++) {
            out << _point[v][u].x() << " " << _point[v][u].y() << " " << _point[v][u].z() << endl;
        }
    }
}

//------------------------------------------------------------------------------
// clear
void Surface3D::clear() {
    erase();
    _m = 2;
    _n = 2;
    clip();
    create();
}

//------------------------------------------------------------------------------
// preset
void Surface3D::preset() {
    erase();
    _m = 4;
    _n = 4;
    clip();
    create();
}

//------------------------------------------------------------------------------
// next coordinate
void Surface3D::next(bool u, bool v) {
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
void Surface3D::previous(bool u, bool v) {
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
void Surface3D::first(bool u, bool v) {
    if (u) {
        _u = 0;
    }
    if (v) {
        _v = 0;
    }
}

//------------------------------------------------------------------------------
// last coordinate
void Surface3D::last(bool u, bool v) {
    if (u) {
        _u = _m - 1;
    }
    if (v) {
        _v = _n - 1;
    }
}

//------------------------------------------------------------------------------
// wrap coordinates
void Surface3D::wrap() {
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
void Surface3D::clip() {
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
void Surface3D::modify(double x, double y, double z) {
    _point[_v][_u] += Vectors(x, y, z);
    for (int v = _v - 2; v < _v + 2; v++) {
        if (v >= 0 && v < _n - 1) {
            for (int u = _u - 2; u < _u + 2; u++) {
                if (u >= 0 && u < _m - 1) {
                    _patch[v][u]->modify();
                }
            }
        }
    }
}

//------------------------------------------------------------------------------
// insert
void Surface3D::insert() {
    if (_u < _m - 1 && _v < _n - 1) {
        int u;
        int v;
        // copy old z
        int nOld = _n;
        Vectors **pointOld = _point;
        for (v = 0; v < _n; v++) {
            pointOld[v] = _point[v];
            for (u = 0; u < _m; u++) {
                pointOld[v][u] = _point[v][u];
            }
        }
        _m++;
        _n++;
        // create new z
        _point = new Vectors *[_n];
        for (v = 0; v < _n; v++) {
            _point[v] = new Vectors[_m];
            for (int u = 0; u < _m; u++) {
                if (v <= _v) {
                    if (u <= _u) {
                        _point[v][u] = pointOld[v][u];
                    }
                    else if (u == _u + 1) {
                        _point[v][u] = 0.5 * (pointOld[v][u - 1] + pointOld[v][u]);
                    }
                    else {
                        _point[v][u] = pointOld[v][u - 1];
                    }
                }
                else if (v == _v + 1) {
                    if (u <= _u) {
                        _point[v][u] = 0.5 * (pointOld[v - 1][u] + pointOld[v][u]);
                    }
                    else if (u == _u + 1) {
                        _point[v][u] = 0.25 * (pointOld[v - 1][u - 1] + pointOld[v - 1][u]
                            + pointOld[v][u - 1] + pointOld[v][u]);
                    }
                    else {
                        _point[v][u] = 0.5 * (pointOld[v - 1][u - 1] + pointOld[v][u - 1]);
                    }
                }
                else {
                    if (u <= _u) {
                        _point[v][u] = pointOld[v - 1][u];
                    }
                    else if (u == _u + 1) {
                        _point[v][u] = 0.5 * (pointOld[v - 1][u - 1] + pointOld[v - 1][u]);
                    }
                    else {
                        _point[v][u] = pointOld[v - 1][u - 1];
                    }
                }
            }
        }
        // erase patch
        for (v = 0; v < _n - 2; v++) {
            for (u = 0; u < _m - 2; u++) {
                delete _patch[v][u];
            }
            delete[] _patch[v];
        }
        delete[] _patch;
        // create patch
        _patch = new Patch3D **[_n - 1];
        for (v = 0; v < _n - 1; v++) {
            _patch[v] = new Patch3D *[_m - 1];
            for (u = 0; u < _m - 1; u++) {
                _patch[v][u] = new Patch3D(u, v, _tiles);
            }
        }
        // erase old z
        for (v = 0; v < nOld; v++) {
            delete[] pointOld[v];
        }
        delete[] pointOld;
        _u++;
        _v++;
    }
}

//------------------------------------------------------------------------------
// remove
void Surface3D::remove() {
    if (_u > 0 && _u < _m - 1 && _v > 0 && _v < _n - 1 && _m > 2 && _n > 2) {
        int u;
        int v;
        // copy old z
        int nOld = _n;
        Vectors **pointOld = _point;
        for (v = 0; v < _n; v++) {
            pointOld[v] = _point[v];
            for (u = 0; u < _m; u++) {
                pointOld[v][u] = _point[v][u];
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
        _point = new Vectors *[_n];
        for (v = 0; v < _n; v++) {
            _point[v] = new Vectors[_m];
            for (int u = 0; u < _m; u++) {
                if (v < _v) {
                    if (u < _u) {
                        _point[v][u] = pointOld[v][u];
                    }
                    else {
                        _point[v][u] = pointOld[v][u + 1];
                    }
                }
                else {
                    if (u < _u) {
                        _point[v][u] = pointOld[v + 1][u];
                    }
                    else {
                        _point[v][u] = pointOld[v + 1][u + 1];
                    }
                }
            }
        }
        _patch = new Patch3D **[_n - 1];
        for (v = 0; v < _n - 1; v++) {
            _patch[v] = new Patch3D *[_m - 1];
            for (u = 0; u < _m - 1; u++) {
                _patch[v][u] = new Patch3D(u, v, _tiles);
            }
        }
        // erase old z
        for (v = 0; v < nOld; v++) {
            delete[] pointOld[v];
        }
        delete[] pointOld;
        _u--;
        _v--;
    }
}

//------------------------------------------------------------------------------
// render
void Surface3D::render(bool markers, bool wireframe, bool hull, bool solid, bool axes, bool texture) {
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
    if (hull) {
        // highlight control point hull
        glDisable(GL_LIGHTING);
        glPushMatrix();
        glTranslated(0.0, 0.0, 0.002);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBegin(GL_QUADS);
        glColor3d(1.0, 1.0, 0.0);
        for (int v = 0; v < _n - 1; v++) {
            for (int u = 0; u < _m - 1; u++) {
                double point[3];
                glVertex3dv(_point[v][u].toDouble(point));
                u++;
                glVertex3dv(_point[v][u].toDouble(point));
                v++;
                glVertex3dv(_point[v][u].toDouble(point));
                u--;
                glVertex3dv(_point[v][u].toDouble(point));
                v--;
            }
        }
        glEnd();
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glPopMatrix();
        glEnable(GL_LIGHTING);
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
        for (int v = 0; v < _n; v++) {
            for (int u = 0; u < _m; u++) {
                glPushMatrix();
                glTranslated(_point[v][u].x(), _point[v][u].y(), _point[v][u].z());
                GLUquadricObj *sphere = gluNewQuadric();
                gluQuadricDrawStyle(sphere, GLU_FILL);
                gluQuadricNormals(sphere, GLU_SMOOTH);
                gluSphere(sphere, 0.01, 4, 2);
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
        glTranslated(_point[_v][_u].x(), _point[_v][_u].y(), _point[_v][_u].z());
        GLUquadricObj *sphere1 = gluNewQuadric();
        gluQuadricDrawStyle(sphere1, GLU_FILL);
        gluQuadricNormals(sphere1, GLU_SMOOTH);
        gluSphere(sphere1, 0.02, 20, 10);
        gluDeleteQuadric(sphere1);
        glPopMatrix();
    }
    if (axes) {
        // highlight current control point axes
        glDisable(GL_LIGHTING);
        glPushMatrix();
        glTranslated(_point[_v][_u].x(), _point[_v][_u].y(), _point[_v][_u].z());
        glBegin(GL_LINES);
        glColor3d(1.0, 0.0, 0.0);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(0.2, 0.0, 0.0);
        glColor3d(0.0, 1.0, 0.0);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(0.0, 0.2, 0.0);
        glColor3d(0.0, 0.0, 1.0);
        glVertex3d(0.0, 0.0, 0.0);
        glVertex3d(0.0, 0.0, 0.2);
        glEnd();
        glPopMatrix();
        glEnable(GL_LIGHTING);
    }
    _texture.render();
    if (solid) {
        glPolygonMode(GL_FRONT_AND_BACK, !wireframe ? GL_FILL : GL_LINE);
        for (int v = 0; v < _n - 1; v++) {
            for (int u = 0; u < _m - 1; u++) {
                _patch[v][u]->render(_point, _m, _n, texture);
            }
        }
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    glPopMatrix();
}

//------------------------------------------------------------------------------
// rotate
void Surface3D::rotate(double x, double y, double z) {
    _angleX += x;
    _angleY += y;
    _angleZ += z;
}

//------------------------------------------------------------------------------
// play spin
void Surface3D::play() {
    _spin = !_spin;
}

//------------------------------------------------------------------------------
// set spin axis
void Surface3D::spin() {
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
void Surface3D::stop() {
    _spin = false;
    _angleX = 0.0;
    _angleY = 0.0;
    _angleZ = 0.0;
}

//------------------------------------------------------------------------------
// double tiles
void Surface3D::doubleTiles() {
    _tiles *= 2;
    for (int v = 0; v < _n - 1; v++) {
        for (int u = 0; u < _m - 1; u++) {
            _patch[v][u]->tiles(_tiles);
        }
    }
}

//------------------------------------------------------------------------------
// half tiles
void Surface3D::halfTiles() {
    _tiles /= 2;
    if (_tiles < 1) {
        _tiles = 1;
    }
    for (int v = 0; v < _n - 1; v++) {
        for (int u = 0; u < _m - 1; u++) {
            _patch[v][u]->tiles(_tiles);
        }
    }
}

//------------------------------------------------------------------------------
// texture
void Surface3D::texture() {
    _texture.read();
}

//------------------------------------------------------------------------------
// mesh
void Surface3D::mesh(const string &filename) const {
    ofstream out(filename.c_str());
    if (!out.good()) {
        throw string("Error : Invalid file name = " + filename);
    }
    out << "Screen {" << endl;
    out << "Width 600" << endl;
    out << "Height 600" << endl;
    out << "Background 0.75 0.75 0.75" << endl;

    out << "Camera {" << endl;
    out << "Rotation 0.0 0.0 0.0" << endl;
    out << "Distance 0.0" << endl;
    out << "Centre 0.0 0.0 -4.0" << endl;
    out << "FieldOfView " << atan(1.0 / 4.0) * RAD_TO_DEG * 2.0 << endl;
    out << "}" << endl;

    out << "}" << endl;

    out << "Group {" << endl;

    out << "Light {" << endl;
    out << "Infinite false" << endl;
    out << "Centre 0.0 0.0 6.0" << endl;
    out << "Ambient 0.5 0.5 0.5" << endl;
    out << "Diffuse 0.2 0.2 0.2" << endl;
    out << "Specular 0.5 0.5 0.5" << endl;
    out << "}" << endl;

    out << "Light {" << endl;
    out << "Infinite false" << endl;
    out << "Centre 0.0 10.0 -4.0" << endl;
    out << "Ambient 0.0 0.0 0.0" << endl;
    out << "Diffuse 0.2 0.2 0.2" << endl;
    out << "Specular 0.5 0.5 0.5" << endl;
    out << "}" << endl;

    out << "Transformation {" << endl;
    out << "Translate 0.0 0.0 -4.0" << endl;
    out << "}" << endl;

    out << "Transformation {" << endl;
    out << "Axis 0.0 0.0 1.0" << endl;
    out << "Angle " << _angleZ << endl;
    out << "}" << endl;

    out << "Transformation {" << endl;
    out << "Axis 1.0 0.0 0.0" << endl;
    out << "Angle " << _angleX << endl;
    out << "}" << endl;

    out << "Transformation {" << endl;
    out << "Axis 0.0 1.0 0.0" << endl;
    out << "Angle " << _angleY << endl;
    out << "}" << endl;

    for (int v = 0; v < _n - 1; v++) {
        for (int u = 0; u < _m - 1; u++) {
            _patch[v][u]->write(out, _m, _n);
        }
    }

    out << "}" << endl;
}

//------------------------------------------------------------------------------
