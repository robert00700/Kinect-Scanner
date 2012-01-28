#ifndef vectorh
#define vectorh
#include <armadillo>

struct Vector {
  float x;
  float y;
  float z;
  Vector operator+(const Vector& rhs) const;//Vector addition
  Vector operator+=(const Vector& rhs);//Vector addition
  Vector operator-(const Vector& rhs) const;//Vector subtraction
  Vector operator-=(const Vector& rhs);//Vector addition
  Vector operator%(const Vector& rhs) const;//Cross product
  float operator*(const Vector& rhs) const;//Dot Product
  Vector operator*(const float scalar) const;//Scalar multiplication
  Vector operator/(const float scalar) const;//Scalar multiplication
  float mag() const;//Sum of squares
  Vector norm(); //normalizxted
  float dist(const Vector& rhs);//Distance to another vector
  float angle(const Vector& rhs);//Angle between vectors
  Vector(float x, float y, float z);
  Vector(arma::vec & in);
  Vector(const Vector& in);
  Vector();
};

#endif
