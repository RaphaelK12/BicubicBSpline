//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Patch3D.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <GL/glut.h>
#pragma hdrstop
#include "Patch3D.h"
#include "Vectors.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// constructor
Patch3D::Patch3D(int u, int v, int tiles) :
    _u(u),
    _v(v),
    _tiles(tiles),
    _valid(false) {
    for (int i = 0; i < ORDER; i++) {
        for (int j = 0; j < ORDER; j++) {
            _matrix[i][j] = 0.0;
        }
    }
    create();
}

//------------------------------------------------------------------------------
// destructor
Patch3D::~Patch3D() {
    erase();
}

//------------------------------------------------------------------------------
// copy constructor
Patch3D::Patch3D(const Patch3D &patch3D) {
    copy(patch3D);
}

//------------------------------------------------------------------------------
// assignment operator
Patch3D &Patch3D::operator=(const Patch3D &patch3D) {
    if (this != &patch3D) {
        erase();
        copy(patch3D);
    }
    return *this;
}

//------------------------------------------------------------------------------
// create
void Patch3D::create() {
    _vertex = new Vectors *[(_tiles + 1)];
    _normal = new Vectors *[(_tiles + 1)];
    for (int v = 0; v < (_tiles + 1); v++) {
        _vertex[v] = new Vectors[(_tiles + 1)];
        _normal[v] = new Vectors[(_tiles + 1)];
    }
}

//------------------------------------------------------------------------------
// erase
void Patch3D::erase() {
    for (int v = 0; v < (_tiles + 1); v++) {
        delete[] _vertex[v];
        delete[] _normal[v];
    }
    delete[] _vertex;
    delete[] _normal;
}

//------------------------------------------------------------------------------
// copy
void Patch3D::copy(const Patch3D &patch3D) {
    _u = patch3D._u;
    _v = patch3D._v;
    _valid = patch3D._valid;
    _tiles = patch3D._tiles;
    for (int i = 0; i < ORDER; i++) {
        for (int j = 0; j < ORDER; j++) {
            _matrix[i][j] = patch3D._matrix[i][j];
        }
    }
    create();
    for (int v = 0; v < (_tiles + 1); v++) {
        for (int u = 0; u < (_tiles + 1); u++) {
            _vertex[v][u] = patch3D._vertex[v][u];
            _normal[v][u] = patch3D._normal[v][u];
        }
    }
}

//------------------------------------------------------------------------------
// tiles
void Patch3D::tiles(int tiles) {
    _valid = false;
    erase();
    _tiles = tiles;
    create();
}

//------------------------------------------------------------------------------
// modify
void Patch3D::modify() {
    _valid = false;
}

//------------------------------------------------------------------------------
// render
void Patch3D::render(Vectors **point, int m, int n, bool texture) {
    if (!_valid) {
        _valid = true;
        matrices(point, m, n);
        vertices();
        normals();
    }
    double r = (double)_u / (double)(m - 2);
    double g = (double)_v / (double)(n - 2);
    double b = (1.0 - r) * (1.0 - g);
    GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat ambient[] = { r, g, b, 1.0 };
    GLfloat diffuse[] = { r, g, b, 1.0 };
    GLfloat specular[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat shininess = 10.0;
    GLfloat emission[] = { 0.0, 0.0, 0.0, 0.0 };
    if (texture) {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, white);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
    }
    else {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    }
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
    if (texture) {
        glEnable(GL_TEXTURE_2D);
    }
    glBegin(GL_QUADS);
    for (int i = 0; i < _tiles; i++) {
        for (int j = 0; j < _tiles; j++) {
            int u = _u * _tiles + j;
            int v = _v * _tiles + i;
            double point[3];
            glTexCoord2d((double)u / (double)((m - 1) * _tiles),
                (double)v / (double)((n - 1) * _tiles));
            glNormal3dv(_normal[i][j].toDouble(point));
            glVertex3dv(_vertex[i][j].toDouble(point));
            u++;
            glTexCoord2d((double)u / (double)((m - 1) * _tiles),
                (double)v / (double)((n - 1) * _tiles));
            glNormal3dv(_normal[i][j + 1].toDouble(point));
            glVertex3dv(_vertex[i][j + 1].toDouble(point));
            v++;
            glTexCoord2d((double)u / (double)((m - 1) * _tiles),
                (double)v / (double)((n - 1) * _tiles));
            glNormal3dv(_normal[i + 1][j + 1].toDouble(point));
            glVertex3dv(_vertex[i + 1][j + 1].toDouble(point));
            u--;
            glTexCoord2d((double)u / (double)((m - 1) * _tiles),
                (double)v / (double)((n - 1) * _tiles));
            glNormal3dv(_normal[i + 1][j].toDouble(point));
            glVertex3dv(_vertex[i + 1][j].toDouble(point));
            v--;
        }
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

//------------------------------------------------------------------------------
// matrices
void Patch3D::matrices(Vectors **point, int m, int n) {
    int i;
    int j;
    int k;
    Vectors Z[ORDER][ORDER];
    for (i = 0; i < ORDER; i++) {
        for (j = 0; j < ORDER; j++) {
            int v = _v + j - 1;
            v = (v < 0) ? 0 : ((v > n - 1) ? n - 1 : v);
            int u = _u + i - 1;
            u = (u < 0) ? 0 : ((u > m - 1) ? m - 1 : u);
            Z[i][j] = point[v][u];
        }
    }
    double B[ORDER][ORDER] = {
        { -1.0 / 6.0,  3.0 / 6.0, -3.0 / 6.0, 1.0 / 6.0 },
        {  3.0 / 6.0, -6.0 / 6.0,  3.0 / 6.0, 0.0 / 6.0 },
        { -3.0 / 6.0,  0.0 / 6.0,  3.0 / 6.0, 0.0 / 6.0 },
        {  1.0 / 6.0,  4.0 / 6.0,  1.0 / 6.0, 0.0 / 6.0 }};
    Vectors BZ[ORDER][ORDER];
    for (i = 0; i < ORDER; i++) {
        for (j = 0; j < ORDER; j++) {
            BZ[i][j] = 0.0;
            for (k = 0; k < ORDER; k++) {
                BZ[i][j] += B[i][k] * Z[k][j];
            }
        }
    }
    for (i = 0; i < ORDER; i++) {
        for (j = 0; j < ORDER; j++) {
            _matrix[i][j] = Vectors();
            for (k = 0; k < ORDER; k++) {
                _matrix[i][j] += BZ[i][k] * B[j][k];
            }
        }
    }
}

//------------------------------------------------------------------------------
// vertices
void Patch3D::vertices() {
    for (int v = 0; v < (_tiles + 1); v++) {
        double y = (double)v / (double)_tiles;
        for (int u = 0; u < (_tiles + 1); u++) {
            double x = (double)u / (double)_tiles;
            Vectors T[ORDER];
            for (int j = 0; j < ORDER; j++) {
                T[j] = _matrix[0][j];
                for (int k = 1; k < ORDER; k++) {
                    T[j] = x * T[j] + _matrix[k][j];
                }
            }
            _vertex[v][u] = T[0];
            for (int k = 1; k < ORDER; k++) {
                _vertex[v][u] = y * _vertex[v][u] + T[k];
            }
        }
    }
}

//------------------------------------------------------------------------------
// normals
void Patch3D::normals() {
    for (int v = 0; v < (_tiles + 1); v++) {
        double y = (double)v / (double)_tiles;
        for (int u = 0; u < (_tiles + 1); u++) {
            double x = (double)u / (double)_tiles;
            int j;
            int k;
            Vectors T[ORDER];
            // d/du tangent
            for (j = 0; j < ORDER; j++) {
                T[j] = (double)(ORDER - 1) * _matrix[0][j];
                for (k = 1; k < ORDER - 1; k++) {
                    T[j] = x * T[j] + (double)(ORDER - 1 - k) * _matrix[k][j];
                }
            }
            Vectors du = T[0];
            for (k = 1; k < ORDER; k++) {
                du = y * du + T[k];
            }
            // d/dv tangent
            for (j = 0; j < ORDER; j++) {
                T[j] = _matrix[0][j];
                for (k = 1; k < ORDER; k++) {
                    T[j] = x * T[j] + _matrix[k][j];
                }
            }
            Vectors dv = (double)(ORDER - 1) * T[0];
            for (k = 1; k < ORDER - 1; k++) {
                dv = y * dv + (double)(ORDER - 1 - k) * T[k];
            }
            // cross product
            _normal[v][u] = du.cross(dv).unit();
        }
    }
}

//------------------------------------------------------------------------------
// write
void Patch3D::write(ostream &out, int m, int n) const {
    out << "Group {" << endl;
    out << "Intersection {" << endl;
    int u;
    int v;
    double xMin = INFINITY;
    double xMax = -INFINITY;
    double yMin = INFINITY;
    double yMax = -INFINITY;
    double zMin = INFINITY;
    double zMax = -INFINITY;
    for (v = 0; v < (_tiles + 1); v++) {
        for (u = 0; u < (_tiles + 1); u++) {
            if (_vertex[v][u].x() < xMin) {
                xMin = _vertex[v][u].x();
            }
            if (_vertex[v][u].x() > xMax) {
                xMax = _vertex[v][u].x();
            }
            if (_vertex[v][u].y() < yMin) {
                yMin = _vertex[v][u].y();
            }
            if (_vertex[v][u].y() > yMax) {
                yMax = _vertex[v][u].y();
            }
            if (_vertex[v][u].z() < zMin) {
                zMin = _vertex[v][u].z();
            }
            if (_vertex[v][u].z() > zMax) {
                zMax = _vertex[v][u].z();
            }
        }
    }
    const double BORDER = 0.001;
    out << "Plane {" << endl;
    out << "Normal -1.0 0.0 0.0" << endl;
    out << "Up 0.0 1.0 0.0" << endl;
    out << "Centre " << xMin - BORDER << " 0.0 0.0" << endl;
    out << "Visible false" << endl;
    out << "}" << endl;
    out << "Plane {" << endl;
    out << "Normal 1.0 0.0 0.0" << endl;
    out << "Up 0.0 1.0 0.0" << endl;
    out << "Centre " << xMax + BORDER << " 0.0 0.0" << endl;
    out << "Visible false" << endl;
    out << "}" << endl;
    out << "Plane {" << endl;
    out << "Normal 0.0 -1.0 0.0" << endl;
    out << "Up 1.0 0.0 0.0" << endl;
    out << "Centre 0.0 " << yMin - BORDER << " 0.0" << endl;
    out << "Visible false" << endl;
    out << "}" << endl;
    out << "Plane {" << endl;
    out << "Normal 0.0 1.0 0.0" << endl;
    out << "Up 1.0 0.0 0.0" << endl;
    out << "Centre 0.0 " << yMax + BORDER << " 0.0" << endl;
    out << "Visible false" << endl;
    out << "}" << endl;
    out << "Plane {" << endl;
    out << "Normal 0.0 0.0 -1.0" << endl;
    out << "Up 1.0 0.0 0.0" << endl;
    out << "Centre 0.0 0.0 " << zMin - BORDER << endl;
    out << "Visible false" << endl;
    out << "}" << endl;
    out << "Plane {" << endl;
    out << "Normal 0.0 0.0 1.0" << endl;
    out << "Up 1.0 0.0 0.0" << endl;
    out << "Centre 0.0 0.0 " << zMax + BORDER << endl;
    out << "Visible false" << endl;
    out << "}" << endl;
    out << "Union {" << endl;
    out << "Mesh {" << endl;
    double r = (double)_u / (double)(m - 2);
    double g = (double)_v / (double)(n - 2);
    double b = (1.0 - r) * (1.0 - g);
    out << "Material {" << endl;
    out << "Ambient " << r << " " << g << " " << b << endl;
    out << "Diffuse " << r << " " << g << " " << b << endl;
    out << "Specular 0.5 0.5 0.5" << endl;
    out << "Shininess 10.0" << endl;
    out << "Reflection 0.2 0.2 0.2" << endl;
    out << "}" << endl;
    out << "Vertex {" << endl;
    for (v = 0; v < (_tiles + 1); v++) {
        for (u = 0; u < (_tiles + 1); u++) {
            out << "Vertex " << _vertex[v][u] << endl;
        }
    }
    out << "}" << endl;
    out << "Normal {" << endl;
    for (v = 0; v < (_tiles + 1); v++) {
        for (u = 0; u < (_tiles + 1); u++) {
            out << "Normal " << _normal[v][u] << endl;
        }
    }
    out << "}" << endl;
    out << "Face {" << endl;
    for (v = 0; v < _tiles; v++) {
        for (u = 0; u < _tiles; u++) {
            out << "Face " <<
                (v * (_tiles + 1) + u) << " " <<
                (v * (_tiles + 1) + u + 1) << " " <<
                ((v + 1) * (_tiles + 1) + u + 1) << endl;
            out << "Face " <<
                (v * (_tiles + 1) + u) << " " <<
                ((v + 1) * (_tiles + 1) + u + 1) << " " <<
                ((v + 1) * (_tiles + 1) + u) << endl;
        }
    }
    out << "}" << endl;
    out << "Smooth true" << endl;
    out << "}" << endl;
    out << "}" << endl;
    out << "}" << endl;
    out << "}" << endl;
}

//------------------------------------------------------------------------------
