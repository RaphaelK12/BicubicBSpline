//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Control.cpp
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <process.h>
#include <GL/glut.h>
#pragma hdrstop
#include "Control.h"
#include "Constants.h"
#include "Test.h"
#include "Circle.h"
#include "Sphere.h"
#include "Surface1D.h"
#include "Surface3D.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;
using namespace ComputerGraphics;

//------------------------------------------------------------------------------
// init
void Control::init(int argc, char **argv) {
    // display menu
    cout << "Press <escape>               to exit program" << endl;
    cout << "Press <f1>                   to select 1D curve" << endl;
    cout << "Press <f2>                   to select 2D curve" << endl;
    cout << "Press <f3>                   to select 3D curve" << endl;
    cout << "Press <f4>                   to select 1D surface" << endl;
    cout << "Press <f5>                   to select 3D surface" << endl;
    cout << "Press <f6>                   to preset" << endl;
    cout << "Press <f7>                   to read" << endl;
    cout << "Press <f8>                   to clear" << endl;
    cout << "Press <f9>                   to spin" << endl;
    cout << "Press <f10>                  to select spin axis" << endl;
    cout << "Press <f11>                  to stop spin" << endl;
    cout << "Press <1>                    to display markers" << endl;
    cout << "Press <2>                    to display hull" << endl;
    cout << "Press <3>                    to display axes" << endl;
    cout << "Press <4>                    to display wireframe" << endl;
    cout << "Press <5>                    to display solid" << endl;
    cout << "Press <6>                    to display texture" << endl;
    cout << "Press <7>                    to animate" << endl;
    cout << "Press <8>                    to write" << endl;
    cout << "Press <9>                    to ray-trace" << endl;
    cout << "Press <enter>                to rotate" << endl;
    cout << "Press <insert>               to insert" << endl;
    cout << "Press <delete>               to delete" << endl;
    cout << "Press <left or down>         to select previous" << endl;
    cout << "Press <right or up>          to select next" << endl;
    cout << "Press <home or pagedown>     to select first" << endl;
    cout << "Press <end or pageup>        to select last" << endl;
    cout << "Press < or >                 to select tiles" << endl;
    cout << "Press left mouse button      to adjust x and y coordinates" << endl;
    cout << "Press right mouse button     to adjust z coordinate" << endl;
    // initialize OpenGL
    glutReshapeWindow(WIDTH, HEIGHT);
    glViewport(0, 0, WIDTH, HEIGHT);
    glClearColor(0.75, 0.75, 0.75, 0.0);
    glClearDepth(1.0);
    glShadeModel(GL_SMOOTH);
    GLfloat ambient[] = {0.0, 0.0, 0.0, 0.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    //glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
    GLfloat position0[] = { 0.0, 0.0, 10.0, 1.0 };
    GLfloat ambient0[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat diffuse0[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat specular0[] = { 0.5, 0.5, 0.5, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, position0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
    glEnable(GL_LIGHT0);
    GLfloat position1[] = { 0.0, 10.0, 0.0, 1.0 };
    GLfloat ambient1[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat diffuse1[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat specular1[] = { 0.5, 0.5, 0.5, 1.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, position1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
    glEnable(GL_LIGHT1);
    // initialize curves
    _test.preset(_curve1D, "../Data/Test.txt");
    _circle.preset(_curve2D);
    _sphere.preset(_curve3D);
    _surface3D.texture();
}

//------------------------------------------------------------------------------
// display
void Control::display() {
    time_t start;
    start = clock();
    // plot curve
    double aspectRatio = (double)glutGet(GLUT_WINDOW_WIDTH) / (double)glutGet(GLUT_WINDOW_HEIGHT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    switch (_dimension) {
        case CURVE_1D: {
            _curve1D.render(_markers, _animation);
            break;
        }
        case CURVE_2D: {
            _curve2D.render(_markers, _animation);
            break;
        }
        case CURVE_3D: {
            _curve3D.render(_markers, _animation);
            break;
        }
        case SURFACE_1D: {
            _surface1D.render(_markers);
            break;
        }
        case SURFACE_3D: {
            _surface3D.render(_markers, _wireframe, _hull, _solid, _axes, _texture);
            break;
        }
    }
    // report time and status
    time_t finish;
    finish = clock();
    ostringstream oss;
    oss << setiosflags(ios::fixed) << setprecision(3);
    oss << "Bicubic B-Spline - ";
    switch (_dimension) {
        case CURVE_1D: {
            oss << "Curve in One Dimension - ";
            break;
        }
        case CURVE_2D: {
            oss << "Curve in Two Dimensions - ";
            break;
        }
        case CURVE_3D: {
            oss << "Curve in Three Dimensions - ";
            break;
        }
        case SURFACE_1D: {
            oss << "Surface in One Dimension - ";
            break;
        }
        case SURFACE_3D: {
            oss << "Surface in Three Dimensions - ";
            break;
        }
    }
    oss << (double)(finish - start) / (double)CLOCKS_PER_SEC << " seconds";
    glutSetWindowTitle(oss.str().c_str());
    glutSwapBuffers();
}

//------------------------------------------------------------------------------
// reshape
void Control::reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(atan(1.0 / 4.0) * RAD_TO_DEG * 2.0, 1.0, 0.1, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glutPostRedisplay();
}

//------------------------------------------------------------------------------
// keyboard
void Control::keyboard(unsigned char key, int /*x*/, int /*y*/) {
    const int DELETE = 0x7F;
    const int ESCAPE = 0x1B;
    const int ENTER = 0x0D;
    switch (key) {
        case '1': {
            _markers = !_markers;
            break;
        }
        case '2': {
            _hull = !_hull;
            break;
        }
        case '3': {
            _axes = !_axes;
            break;
        }
        case '4': {
            _wireframe = !_wireframe;
            break;
        }
        case '5': {
            _solid = !_solid;
            break;
        }
        case '6': {
            _texture = !_texture;
            break;
        }
        case '7': {
            _animation = !_animation;
            break;
        }
        case '8': {
            switch (_dimension) {
                case CURVE_1D: {
                    _curve1D.write("../Data/Curve1D.txt");
                    break;
                }
                case CURVE_2D: {
                    _curve2D.write("../Data/Curve2D.txt");
                    break;
                }
                case CURVE_3D: {
                    _curve3D.write("../Data/Curve3D.txt");
                    break;
                }
                case SURFACE_1D: {
                    _surface1D.write("../Data/Surface1D.txt");
                    break;
                }
                case SURFACE_3D: {
                    _surface3D.write("../Data/Surface3D.txt");
                    break;
                }
            }
            break;
        }
        case '9': {
            cout << "Ray-Tracer" << endl;
            _surface3D.mesh("../Data/RayTracer.txt");
            _spawnl(_P_WAIT, "../../RayTracer/Executable/RayTracer.exe",
                "../../RayTracer/Executable/RayTracer.exe",
                "../Data/RayTracer.txt", "../Data/RayTracer.bmp", NULL);
            break;
        }
        case '<': {
            _surface3D.halfTiles();
            break;
        }
        case '>': {
            _surface3D.doubleTiles();
            break;
        }
        case ENTER: {
            _rotate = !_rotate;
            break;
        }
        case DELETE: {
            switch (_dimension) {
                case CURVE_1D: {
                    _curve1D.remove();
                    break;
                }
                case CURVE_2D: {
                    _curve2D.remove();
                    break;
                }
                case CURVE_3D: {
                    _curve3D.remove();
                    break;
                }
                case SURFACE_1D: {
                    _surface1D.remove();
                    break;
                }
                case SURFACE_3D: {
                    _surface3D.remove();
                    break;
                }
            }
            break;
        }
        case ESCAPE: {
            glutDestroyWindow(glutGetWindow());
            delete this;
            exit(0);
        }
    }
}

//------------------------------------------------------------------------------
// special
void Control::special(int key, int /*x*/, int /*y*/) {
    switch (key) {
        case GLUT_KEY_F1: {
            _dimension = CURVE_1D;
            break;
        }
        case GLUT_KEY_F2: {
            _dimension = CURVE_2D;
            break;
        }
        case GLUT_KEY_F3: {
            _dimension = CURVE_3D;
            break;
        }
        case GLUT_KEY_F4: {
            _dimension = SURFACE_1D;
            break;
        }
        case GLUT_KEY_F5: {
            _dimension = SURFACE_3D;
            break;
        }
        case GLUT_KEY_F6: {
            switch (_dimension) {
                case CURVE_1D: {
                    _test.preset(_curve1D, "../Data/Test.txt");
                    break;
                }
                case CURVE_2D: {
                    _circle.preset(_curve2D);
                    break;
                }
                case CURVE_3D: {
                    _sphere.preset(_curve3D);
                    break;
                }
                case SURFACE_1D: {
                    _surface1D.preset();
                    break;
                }
                case SURFACE_3D: {
                    _surface3D.preset();
                    break;
                }
            }
            break;
        }
        case GLUT_KEY_F7: {
            switch (_dimension) {
                case CURVE_1D: {
                    _curve1D.read("../Data/Curve1D.txt");
                    break;
                }
                case CURVE_2D: {
                    _curve2D.read("../Data/Curve2D.txt");
                    break;
                }
                case CURVE_3D: {
                    _curve3D.read("../Data/Curve3D.txt");
                    break;
                }
                case SURFACE_1D: {
                    _surface1D.read("../Data/Surface1D.txt");
                    break;
                }
                case SURFACE_3D: {
                    _surface3D.read("../Data/Surface3D.txt");
                    break;
                }
            }
            break;
        }
        case GLUT_KEY_F8: {
            switch (_dimension) {
                case CURVE_1D: {
                    _curve1D.clear();
                    break;
                }
                case CURVE_2D: {
                    _curve2D.clear();
                    break;
                }
                case CURVE_3D: {
                    _curve3D.clear();
                    break;
                }
                case SURFACE_1D: {
                    _surface1D.clear();
                    break;
                }
                case SURFACE_3D: {
                    _surface3D.clear();
                    break;
                }
            }
            break;
        }
        case GLUT_KEY_F9: {
            switch (_dimension) {
                case CURVE_3D: {
                    _curve3D.play();
                    break;
                }
                case SURFACE_1D: {
                    _surface1D.play();
                    break;
                }
                case SURFACE_3D: {
                    _surface3D.play();
                    break;
                }
            }
            break;
        }
        case GLUT_KEY_F10: {
            switch (_dimension) {
                case CURVE_3D: {
                    _curve3D.spin();
                    break;
                }
                case SURFACE_1D: {
                    _surface1D.spin();
                    break;
                }
                case SURFACE_3D: {
                    _surface3D.spin();
                    break;
                }
            }
            break;
        }
        case GLUT_KEY_F11: {
            switch (_dimension) {
                case CURVE_3D: {
                    _curve3D.stop();
                    break;
                }
                case SURFACE_1D: {
                    _surface1D.stop();
                    break;
                }
                case SURFACE_3D: {
                    _surface3D.stop();
                    break;
                }
            }
            break;
        }
    }
    switch (_dimension) {
        case CURVE_1D: {
            switch (key) {
                case GLUT_KEY_INSERT: {
                    _curve1D.insert();
                    break;
                }
                case GLUT_KEY_LEFT: {
                    _curve1D.previous();
                    break;
                }
                case GLUT_KEY_RIGHT: {
                    _curve1D.next();
                    break;
                }
                case GLUT_KEY_DOWN: {
                    _curve1D.previous();
                    break;
                }
                case GLUT_KEY_UP: {
                    _curve1D.next();
                    break;
                }
                case GLUT_KEY_HOME: {
                    _curve1D.first();
                    break;
                }
                case GLUT_KEY_END: {
                    _curve1D.last();
                    break;
                }
            }
            break;
        }
        case CURVE_2D: {
            switch (key) {
                case GLUT_KEY_INSERT: {
                    _curve2D.insert();
                    break;
                }
                case GLUT_KEY_LEFT: {
                    _curve2D.previous();
                    break;
                }
                case GLUT_KEY_RIGHT: {
                    _curve2D.next();
                    break;
                }
                case GLUT_KEY_DOWN: {
                    _curve2D.previous();
                    break;
                }
                case GLUT_KEY_UP: {
                    _curve2D.next();
                    break;
                }
                case GLUT_KEY_HOME: {
                    _curve2D.first();
                    break;
                }
                case GLUT_KEY_END: {
                    _curve2D.last();
                    break;
                }
            }
            break;
        }
        case CURVE_3D: {
            switch (key) {
                case GLUT_KEY_INSERT: {
                    _curve3D.insert();
                    break;
                }
                case GLUT_KEY_LEFT: {
                    _curve3D.previous();
                    break;
                }
                case GLUT_KEY_RIGHT: {
                    _curve3D.next();
                    break;
                }
                case GLUT_KEY_DOWN: {
                    _curve3D.previous();
                    break;
                }
                case GLUT_KEY_UP: {
                    _curve3D.next();
                    break;
                }
                case GLUT_KEY_HOME: {
                    _curve3D.first();
                    break;
                }
                case GLUT_KEY_END: {
                    _curve3D.last();
                    break;
                }
            }
            break;
        }
        case SURFACE_1D: {
            switch (key) {
                case GLUT_KEY_INSERT: {
                    _surface1D.insert();
                    break;
                }
                case GLUT_KEY_LEFT: {
                    _surface1D.previous(true, false);
                    break;
                }
                case GLUT_KEY_RIGHT: {
                    _surface1D.next(true, false);
                    break;
                }
                case GLUT_KEY_DOWN: {
                    _surface1D.previous(false, true);
                    break;
                }
                case GLUT_KEY_UP: {
                    _surface1D.next(false, true);
                    break;
                }
                case GLUT_KEY_HOME: {
                    _surface1D.first(true, false);
                    break;
                }
                case GLUT_KEY_END: {
                    _surface1D.last(true, false);
                    break;
                }
                case GLUT_KEY_PAGE_DOWN: {
                    _surface1D.first(false, true);
                    break;
                }
                case GLUT_KEY_PAGE_UP: {
                    _surface1D.last(false, true);
                    break;
                }
            }
            break;
        }
        case SURFACE_3D: {
            switch (key) {
                case GLUT_KEY_INSERT: {
                    _surface3D.insert();
                    break;
                }
                case GLUT_KEY_LEFT: {
                    _surface3D.previous(true, false);
                    break;
                }
                case GLUT_KEY_RIGHT: {
                    _surface3D.next(true, false);
                    break;
                }
                case GLUT_KEY_DOWN: {
                    _surface3D.previous(false, true);
                    break;
                }
                case GLUT_KEY_UP: {
                    _surface3D.next(false, true);
                    break;
                }
                case GLUT_KEY_HOME: {
                    _surface3D.first(true, false);
                    break;
                }
                case GLUT_KEY_END: {
                    _surface3D.last(true, false);
                    break;
                }
                case GLUT_KEY_PAGE_DOWN: {
                    _surface3D.first(false, true);
                    break;
                }
                case GLUT_KEY_PAGE_UP: {
                    _surface3D.last(false, true);
                    break;
                }
            }
            break;
        }
    }
}

//------------------------------------------------------------------------------
// mouse
void Control::mouse(int button, int state, int x, int y) {
    _motionX = x;
    _motionY = y;
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        _axis = false;
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        _axis = true;
    }
}

//------------------------------------------------------------------------------
// motion
void Control::motion(int x, int y) {
    const double INCREMENT = 0.01;
    const double INCREMENT_ROTATE = 0.5;
    switch (_dimension) {
        case CURVE_1D: {
            _curve1D.modify((double)(_motionY - y) * INCREMENT);
            break;
        }
        case CURVE_2D: {
            _curve2D.modify((double)(x - _motionX) * INCREMENT,
                (double)(_motionY - y) * INCREMENT);
            break;
        }
        case CURVE_3D: {
            if (!_rotate) {
                if (!_axis) {
                    _curve3D.modify((double)(x - _motionX) * INCREMENT,
                        (double)(_motionY - y) * INCREMENT, 0.0);
                }
                else {
                    _curve3D.modify(0.0, 0.0,
                        (double)((x - _motionX) + (_motionY - y)) * INCREMENT);
                }
            }
            else {
                if (!_axis) {
                    _curve3D.rotate(-(double)(_motionY - y) * INCREMENT_ROTATE,
                        (double)(x - _motionX) * INCREMENT_ROTATE, 0.0);
                }
                else {
                    _curve3D.rotate(0.0, 0.0,
                        -(double)((x - _motionX) + (_motionY - y)) * INCREMENT_ROTATE);
                }
            }
            break;
        }
        case SURFACE_1D: {
            if (!_rotate) {
                _surface1D.modify((double)((x - _motionX) + (_motionY - y)) * INCREMENT);
            }
            else {
                if (!_axis) {
                    _surface1D.rotate(-(double)(_motionY - y) * INCREMENT_ROTATE,
                        (double)(x - _motionX) * INCREMENT_ROTATE, 0.0);
                }
                else {
                    _surface1D.rotate(0.0, 0.0,
                        -(double)((x - _motionX) + (_motionY - y)) * INCREMENT_ROTATE);
                }
            }
            break;
        }
        case SURFACE_3D: {
            if (!_rotate) {
                if (!_axis) {
                    _surface3D.modify((double)(x - _motionX) * INCREMENT,
                        (double)(_motionY - y) * INCREMENT, 0.0);
                }
                else {
                    _surface3D.modify(0.0, 0.0,
                        (double)((x - _motionX) + (_motionY - y)) * INCREMENT);
                }
            }
            else {
                if (!_axis) {
                    _surface3D.rotate(-(double)(_motionY - y) * INCREMENT_ROTATE,
                        (double)(x - _motionX) * INCREMENT_ROTATE, 0.0);
                }
                else {
                    _surface3D.rotate(0.0, 0.0,
                        -(double)((x - _motionX) + (_motionY - y)) * INCREMENT_ROTATE);
                }
            }
            break;
        }
     }
    _motionX = x;
    _motionY = y;
}

//------------------------------------------------------------------------------
// idle
void Control::idle() {
    glutPostRedisplay();
}

//------------------------------------------------------------------------------
