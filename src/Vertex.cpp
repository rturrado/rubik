#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <cstdlib>
#include <iostream>
#include "Vertex.hpp"

using namespace Rubik::Graphics;

typedef boost::numeric::ublas::vector<GLdouble> Vector;
typedef boost::numeric::ublas::matrix<GLdouble> Matrix;

Vertex::Vertex()
: x(0.0), y(0.0), z(0.0)
{
  // Do nothing
}

Vertex::Vertex(GLdouble xCoord, GLdouble yCoord, GLdouble zCoord)
: x(xCoord), y(yCoord), z(zCoord)
{
  // Do nothing
}

GLdouble Vertex::getX() const
{
  return x;
}

GLdouble Vertex::getY() const
{
  return y;
}

GLdouble Vertex::getZ() const
{
  return z;
}

void Vertex::setX(GLdouble newX)
{
  x = newX;
}

void Vertex::setY(GLdouble newY)
{
  y = newY;
}

void Vertex::setZ(GLdouble newZ)
{
  z = newZ;
}

GLdouble* getRotationMatrixX(GLdouble radians)
{
  //std::cout << "getRotationMatrixX(" << radians << ")" << std::endl;
  static GLdouble rotationMatrixX[9] = { 1, 0, 0,
                                         0, 0, 0,
                                         0, 0, 0 };
  rotationMatrixX[4] =  cos(radians);
  rotationMatrixX[5] =  sin(radians);
  rotationMatrixX[7] = -sin(radians);
  rotationMatrixX[8] =  cos(radians);

  return rotationMatrixX;
}

GLdouble* getRotationMatrixY(GLdouble radians)
{
  //std::cout << "getRotationMatrixY(" << radians << ")" << std::endl;
  static GLdouble rotationMatrixY[9] = { 0, 0, 0,
                                         0, 1, 0,
                                         0, 0, 0 };
  rotationMatrixY[0] =  cos(radians);
  rotationMatrixY[2] = -sin(radians);
  rotationMatrixY[6] =  sin(radians);
  rotationMatrixY[8] =  cos(radians);
  
  return rotationMatrixY;
}

GLdouble* getRotationMatrixZ(GLdouble radians)
{
  //std::cout << "getRotationMatrixZ(" << radians << ")" << std::endl;
  static GLdouble rotationMatrixZ[9] = { 0, 0, 0,
                                         0, 0, 0,
                                         0, 0, 1 };
  rotationMatrixZ[0] =  cos(radians);
  rotationMatrixZ[1] =  sin(radians);
  rotationMatrixZ[3] = -sin(radians);
  rotationMatrixZ[4] =  cos(radians);

  return rotationMatrixZ;
}

typedef GLdouble* (*getRotationMatrixPtr)(GLdouble);

getRotationMatrixPtr rotationMatrix[3] = { getRotationMatrixX,
                                           getRotationMatrixY,
                                           getRotationMatrixZ };

GLdouble* getRotationMatrix(const Plane& plane, GLdouble radians)
{
  return (*rotationMatrix[plane])(radians);
}

void Vertex::rotate(const Plane& plane, const Vertex& axis, GLdouble radians)
{
  // Rotation axis
  Vector a(3);
  a[0] = axis.getX();
  a[1] = axis.getY();
  a[2] = axis.getZ();
  //std::cout << "a: " << a << std::endl;
  // Vertex to rotate
  Vector v(3);
  v[0] = x;
  v[1] = y;
  v[2] = z;
  //std::cout << "v: " << v << std::endl;
  // Translation to rotation axis
  v -= a;
  //std::cout << "v-a: " << v << std::endl;
  // Rotation matrix
  Matrix m(3, 3);
  GLdouble* rm = getRotationMatrix(plane, radians);
  for (unsigned int i = 0; i < m.size1(); i++)
  {
    for (unsigned int j = 0; j < m.size2(); j++)
    {
      m(i, j) = rm[3*i + j];
    }
  }
  //std::cout << "matrix: " << m << std::endl;
  // Resulting vector
  Vector result = prod(m, v);
  //std::cout << "m*v: " << result << std::endl;
  // Translation back
  result += a;
  //std::cout << "m*v+a: " << result << std::endl;
  // Update vertex
  x = result[0];
  y = result[1];
  z = result[2];
  //exit(1);
}
