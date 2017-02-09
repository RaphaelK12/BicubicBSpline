//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Patch1D.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <GL/glut.h>
#pragma hdrstop
#include "Patch1D.h"
#include "Vectors.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// constructor
Patch1D::Patch1D(int u /*= 0*/, int v /*= 0*/) : _u(u), _v(v), _valid(false) {
    for (int i = 0; i < ORDER; i++) {
        for (int j = 0; j < ORDER; j++) {
            _matrix[i][j] = 0.0;
        }
    }
    for (int v1 = 0; v1 < TILES + 1; v1++) {
        for (int u1 = 0; u1 < TILES + 1; u1++) {
            _points[v1][u1] = 0.0;
        }
    }
}

//------------------------------------------------------------------------------
// modify
void Patch1D::modify() {
    _valid = false;
}

//------------------------------------------------------------------------------
// render
void Patch1D::render(double **z, int m, int n) {
    if (!_valid) {
        _valid = true;
        matrix(z, m, n);
        vertices();
        normals();
    }
    GLfloat ambient[] = { (double)_u / (double)(m - 2), 0.0, (double)_v / (double)(n - 2), 1.0 };
    GLfloat diffuse[] = { (double)_u / (double)(m - 2), 0.0, (double)_v / (double)(n - 2), 1.0 };
    GLfloat specular[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat shininess = 10.0;
    GLfloat emission[] = { 0.0, 0.0, 0.0, 0.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
    glBegin(GL_QUADS);
    for (int i = 0; i < TILES; i++) {
        for (int j = 0; j < TILES; j++) {
            int u = _u * TILES + j;
            int v = _v * TILES + i;
            double point[3];
            glNormal3dv(_normal[i][j].toDouble(point));
            glVertex3d((double)u / (double)((m - 1) * TILES) - 0.5,
                (double)v / (double)((n - 1) * TILES) - 0.5, _points[i][j]);
            u++;
            glNormal3dv(_normal[i][j + 1].toDouble(point));
            glVertex3d((double)u / (double)((m - 1) * TILES) - 0.5,
                (double)v / (double)((n - 1) * TILES) - 0.5, _points[i][j + 1]);
            v++;
            glNormal3dv(_normal[i + 1][j + 1].toDouble(point));
            glVertex3d((double)u / (double)((m - 1) * TILES) - 0.5,
                (double)v / (double)((n - 1) * TILES) - 0.5, _points[i + 1][j + 1]);
            u--;
            glNormal3dv(_normal[i + 1][j].toDouble(point));
            glVertex3d((double)u / (double)((m - 1) * TILES) - 0.5,
                (double)v / (double)((n - 1) * TILES) - 0.5, _points[i + 1][j]);
            v--;
        }
    }
    glEnd();
}

//------------------------------------------------------------------------------
// matrix
void Patch1D::matrix(double **z, int m, int n) {
    int i;
    int j;
    int k;
    double Z[ORDER][ORDER];
    for (i = 0; i < ORDER; i++) {
        for (j = 0; j < ORDER; j++) {
            int zv = v() + j - 1;
            zv = (zv < 0) ? 0 : ((zv > n - 1) ? n - 1 : zv);
            int zu = u() + i - 1;
            zu = (zu < 0) ? 0 : ((zu > m - 1) ? m - 1 : zu);
            Z[i][j] = z[zv][zu];
        }
    }
    double B[ORDER][ORDER] = {
        { -1.0 / 6.0,  3.0 / 6.0, -3.0 / 6.0, 1.0 / 6.0 },
        {  3.0 / 6.0, -6.0 / 6.0,  3.0 / 6.0, 0.0 / 6.0 },
        { -3.0 / 6.0,  0.0 / 6.0,  3.0 / 6.0, 0.0 / 6.0 },
        {  1.0 / 6.0,  4.0 / 6.0,  1.0 / 6.0, 0.0 / 6.0 }};
    double BZ[ORDER][ORDER];
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
            _matrix[i][j] = 0.0;
            for (k = 0; k < ORDER; k++) {
                _matrix[i][j] += BZ[i][k] * B[j][k];
            }
        }
    }
}

//------------------------------------------------------------------------------
// vertices
void Patch1D::vertices() {
    for (int v = 0; v < TILES + 1; v++) {
        double y = (double)v / (double)TILES;
        for (int u = 0; u < TILES + 1; u++) {
            double x = (double)u / (double)TILES;
            double T[ORDER];
            for (int j = 0; j < ORDER; j++) {
                T[j] = _matrix[0][j];
                for (int k = 1; k < ORDER; k++) {
                    T[j] = x * T[j] + _matrix[k][j];
                }
            }
            _points[v][u] = T[0];
            for (int k = 1; k < ORDER; k++) {
                _points[v][u] = y * _points[v][u] + T[k];
            }
        }
    }
}

//------------------------------------------------------------------------------
// normals
void Patch1D::normals() {
    for (int v = 0; v < TILES + 1; v++) {
        double y = (double)v / (double)TILES;
        for (int u = 0; u < TILES + 1; u++) {
            double x = (double)u / (double)TILES;
            int j;
            int k;
            double T[ORDER];
            // dZ/dX
            for (j = 0; j < ORDER; j++) {
                T[j] = (double)(ORDER - 1) * _matrix[0][j];
                for (k = 1; k < ORDER - 1; k++) {
                    T[j] = x * T[j] + (double)(ORDER - 1 - k) * _matrix[k][j];
                }
            }
            double dzdx = T[0];
            for (k = 1; k < ORDER; k++) {
                dzdx = y * dzdx + T[k];
            }
            // dZ/dY
            for (j = 0; j < ORDER; j++) {
                T[j] = _matrix[0][j];
                for (k = 1; k < ORDER; k++) {
                    T[j] = x * T[j] + _matrix[k][j];
                }
            }
            double dzdy = (double)(ORDER - 1) * T[0];
            for (k = 1; k < ORDER - 1; k++) {
                dzdy = y * dzdy + (double)(ORDER - 1 - k) * T[k];
            }
            _normal[v][u] = Vectors(-dzdx, -dzdy, 1.0).unit();
        }
    }
}

//------------------------------------------------------------------------------
