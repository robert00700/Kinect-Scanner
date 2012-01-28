#include "Vector.h"
#include <math.h>

Vector::Vector(float _x, float _y, float _z) {
  x = _x;
  y = _y;
  z = _z;
}

Vector::Vector(arma::vec & in) {
  x = in(0);
  y = in(1);
  z = in(2);
}

Vector::Vector(const Vector & in) {
  x = in.x;
  y = in.y;
  z = in.z;
}

Vector::Vector() {
  x = y = z = 0.0f;
}

Vector Vector::operator+(const Vector& rhs) const {
  return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
}

Vector Vector::operator+=(const Vector& rhs) {
  x += rhs.x;
  y += rhs.y;
  z += rhs.z;
  return *this;
}

Vector Vector::operator-(const Vector& rhs) const {
  return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
}

Vector  Vector::operator-=(const Vector& rhs) {
  x -= rhs.x;
  y -= rhs.y;
  z -= rhs.z;
  return *this;
}

Vector Vector::operator%(const Vector& rhs) const {
  return Vector(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x);
}

float Vector::operator*(const Vector& rhs) const {
  return x * rhs.x + y * rhs.y + z * rhs.z;
}

Vector Vector::operator*(const float scalar) const {
  return Vector(x * scalar, y * scalar, z * scalar);
}

Vector Vector::operator/(const float scalar) const {
  return Vector(x / scalar, y / scalar, z / scalar);
}

float Vector::dist(const Vector& rhs) {
  return (*this - rhs).mag();
}

float Vector::angle(const Vector& rhs) {
  return (((*this) * rhs)/ (this->mag() * rhs.mag()));
}

Vector Vector::norm() {
  return *this / mag();
}

float Vector::mag() const {
  return sqrt(x * x + y * y + z * z);
}





