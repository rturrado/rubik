#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include "Coord.hpp"

using namespace Rubik::Graphics;
using namespace std;

typedef boost::numeric::ublas::vector<GLdouble> Vector;
typedef boost::numeric::ublas::matrix<GLdouble> Matrix;

Coord::Coord(unsigned int _x, unsigned int _y, unsigned int _z)
: x(_x), y(_y), z(_z)
{
  // Do nothing
}

Vertex Coord::toVertex() const
{
  // This displacement in cube units is used to center the whole Rubik
  // cube around the global coordinates (0, 0, 0)
  GLdouble displacement = static_cast<GLdouble>(numberOfCubesPerSideLine-1)/2;
  GLdouble _x = (x - displacement) * (cubeSizeLength + cubeSeparation);
  GLdouble _y = (y - displacement) * (cubeSizeLength + cubeSeparation);
  GLdouble _z = (z - displacement) * (cubeSizeLength + cubeSeparation);
  return Vertex(_x, _y, _z);
}

static GLdouble rotationMatrixXAnticlockwise[9] = {  1,  0,  0,
                                                     0,  0,  1,
                                                     0, -1,  0 };
static GLdouble rotationMatrixXClockwise[9]     = {  1,  0,  0,
                                                     0,  0, -1,
                                                     0,  1,  0 };
static GLdouble rotationMatrixYAnticlockwise[9] = {  0,  0, -1,
                                                     0,  1,  0,
                                                     1,  0,  0 };
static GLdouble rotationMatrixYClockwise[9]     = {  0,  0,  1,
                                                     0,  1,  0,
                                                    -1,  0,  0 };
static GLdouble rotationMatrixZAnticlockwise[9] = {  0,  1,  0,
                                                    -1,  0,  0,
                                                     0,  0,  1 };
static GLdouble rotationMatrixZClockwise[9]     = {  0, -1,  0,
                                                     1,  0,  0,
                                                     0,  0,  1 };

GLdouble* getRotationMatrix(const Plane& plane, bool clockwise)
{
  switch (plane)
  {
    case x: return clockwise ? rotationMatrixXClockwise
                             : rotationMatrixXAnticlockwise;
    case y: return clockwise ? rotationMatrixYClockwise
                             : rotationMatrixYAnticlockwise;
    case z: return clockwise ? rotationMatrixZClockwise
                             : rotationMatrixZAnticlockwise;
  }
  return nullptr;
}

// Does a 90º rotation
void Coord::rotate(const Plane& plane, bool clockwise)
{
  // Rotation axis
  GLdouble displacement = static_cast<GLdouble>(numberOfCubesPerSideLine-1)/2;
  Vector a(3);
  a[0] = displacement;
  a[1] = displacement;
  a[2] = displacement;
  // Coord to rotate
  Vector c(3);
  c[0] = x;
  c[1] = y;
  c[2] = z;
  // Translation to rotation axis
  c -= a;
  // Rotation matrix
  Matrix m(3, 3);
  GLdouble* rm = getRotationMatrix(plane, clockwise);
  for (unsigned int i = 0; i < m.size1(); i++)
  {
    for (unsigned int j = 0; j < m.size2(); j++)
    {
      m(i, j) = rm[3*i + j];
    }
  }
  // Resulting vector
  Vector result = prod(m, c);
  // Translation back
  result += a;
  // Update coord
  x = result[0];
  y = result[1];
  z = result[2];
}
