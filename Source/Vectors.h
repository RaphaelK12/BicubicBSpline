//------------------------------------------------------------------------------
//
// Module 08939 : Advanced Graphics
// Bicubic B-Spline Assessment
// Vectors.h
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// include guard

#ifndef Vectors_h
#define Vectors_h

//------------------------------------------------------------------------------
// include files

#include <iostream>
#include <string>
#include <cmath>
#include <GL/glut.h>
#include "Constants.h"

//------------------------------------------------------------------------------
// namespace

using namespace std;

//------------------------------------------------------------------------------
// namespace definition

namespace ComputerGraphics {

    //------------------------------------------------------------------------------
    // class definition

    class Vectors {

    public:

        Vectors(double x = 0.0, double y = 0.0, double z = 0.0) :
            _x(x),
            _y(y),
            _z(z) {
        }
        double x() const { return _x; }
        double y() const { return _y; }
        double z() const { return _z; }
        void x(double x) { _x = x; }
        void y(double y) { _y = y; }
        void z(double z) { _z = z; }
        float *toFloat(float f[]) const {
            f[0] = _x;
            f[1] = _y;
            f[2] = _z;
            return f;
        }
        double *toDouble(double f[]) const {
            f[0] = _x;
            f[1] = _y;
            f[2] = _z;
            return f;
        }
        // add two vectors and copy into this vector
        Vectors &add(const Vectors &v1, const Vectors &v2) {
            _x = v1._x + v2._x;
            _y = v1._y + v2._y;
            _z = v1._z + v2._z;
            return *this;
        }
        Vectors &operator+=(const Vectors &v) {
            return add(*this, v);
        }
        Vectors operator+(const Vectors &v) const {
            return Vectors().add(*this, v);
        }
        // subtract two vectors and copy into this vector
        Vectors &subtract(const Vectors &v1, const Vectors &v2) {
            _x = v1._x - v2._x;
            _y = v1._y - v2._y;
            _z = v1._z - v2._z;
            return *this;
        }
        Vectors &operator-=(const Vectors &v) {
            return subtract(*this, v);
        }
        Vectors operator-(const Vectors &v) const {
            return Vectors().subtract(*this, v);
        }
        // multiply two vectors and copy into this vector
        Vectors &multiply(const Vectors &v1, const Vectors &v2) {
            _x = v1._x * v2._x;
            _y = v1._y * v2._y;
            _z = v1._z * v2._z;
            return *this;
        }
        Vectors &operator*=(const Vectors &v) {
            return multiply(*this, v);
        }
        Vectors operator*(const Vectors &v) const {
            return Vectors().multiply(*this, v);
        }
        // multiply vector by scalar and copy into this vector
        Vectors &multiply(const Vectors &v, double s) {
            _x = v._x * s;
            _y = v._y * s;
            _z = v._z * s;
            return *this;
        }
        Vectors &operator*=(double s) {
            return multiply(*this, s);
        }
        Vectors operator*(double s) const {
            return Vectors().multiply(*this, s);
        }
        // divide vector by scalar and copy into this vector
        Vectors &divide(const Vectors &v, double s) {
            double rs = (fabs(s) < EPSILON) ? 0.0 : 1.0 / s;
            _x = v._x * rs;
            _y = v._y * rs;
            _z = v._z * rs;
            return *this;
        }
        Vectors &operator/=(double s) {
            return divide(*this, s);
        }
        Vectors operator/(double s) const {
            return Vectors().divide(*this, s);
        }
        // cross product between this vector and another vector
        Vectors cross(const Vectors &v) const {
            double vx = _y * v._z - _z * v._y;
            double vy = _z * v._x - _x * v._z;
            double vz = _x * v._y - _y * v._x;
            return Vectors(vx, vy, vz);
        }
        // dot product between this vector and another vector
        double dot(const Vectors &v) const {
            return _x * v._x + _y * v._y + _z * v._z;
        }
        // distance from this vector to another vector
        double distance(const Vectors &v) const {
            return (v - *this).magnitude();
        }
        // magnitude of this vector
        double magnitude() const {
            return sqrt(dot(*this));
        }
        // normalize this vector
        Vectors &normalize() {
            return *this /= magnitude();
        }
        // unit vector of this vector
        Vectors unit() const {
            return *this / magnitude();
        }
        // negate this vector
        Vectors &negate() {
            _x = -_x;
            _y = -_y;
            _z = -_z;
            return *this;
        }
        // negative operator-
        Vectors operator-() const {
            return Vectors(-_x, -_y, -_z);
        }
        void set(const Vectors &v) {
            _x = v.x();
            _y = v.y();
            _z = v.z();
        }
        void set(double x, double y, double z) {
            _x = x;
            _y = y;
            _z = z;
        }
        friend Vectors operator*(double s, const Vectors &v) {
            return v * s;
        }
        friend istream &operator>>(istream &in, Vectors &v) {
            v.read(in);
            return in;
        }
        friend ostream &operator<<(ostream &out, const Vectors &v) {
            v.write(out);
            return out;
        }

    private:

        void read(istream &in) {
            in >> _x >> _y >> _z;
        }
        void write(ostream &out) const {
            out << _x << " " << _y << " " << _z;
        }

        double _x;
        double _y;
        double _z;

    };

} // ComputerGraphics

#endif // Vectors_h

//------------------------------------------------------------------------------
