#include <GL/gl.h>
#include "Constants.hpp"
#include "Side.hpp"

using namespace Rubik::Graphics;

/*static*/
unsigned int Side::sideCounter = 0;

/*static*/
unsigned int Side::selectedSide = numberOfSides;

/*static*/
void Side::selectSide(unsigned int which)
{
  selectedSide = which;
}

// Vertices are given counterclockwise,
// looking at the side from the outside,
// bottom left, bottom right, top right, top left
//
//   7 _______ 6
//    /|     /|
// 3 /_|___2/ |
//  | 4|___|__|5
//  | /    | /
//  |/_____|/
// 0        1

const GLdouble sideToCenterLength = cubeSizeLength/2;
const GLdouble sTCL = sideToCenterLength;

Vertex getVertex0(const Vertex& cc)
{
  return Vertex(cc.getX() - sTCL, cc.getY() - sTCL, cc.getZ() + sTCL);
}

Vertex getVertex1(const Vertex& cc)
{
  return Vertex(cc.getX() + sTCL, cc.getY() - sTCL, cc.getZ() + sTCL);
}

Vertex getVertex2(const Vertex& cc)
{
  return Vertex(cc.getX() + sTCL, cc.getY() + sTCL, cc.getZ() + sTCL);
}

Vertex getVertex3(const Vertex& cc)
{
  return Vertex(cc.getX() - sTCL, cc.getY() + sTCL, cc.getZ() + sTCL);
}

Vertex getVertex4(const Vertex& cc)
{
  return Vertex(cc.getX() - sTCL, cc.getY() - sTCL, cc.getZ() - sTCL);
}

Vertex getVertex5(const Vertex& cc)
{
  return Vertex(cc.getX() + sTCL, cc.getY() - sTCL, cc.getZ() - sTCL);
}

Vertex getVertex6(const Vertex& cc)
{
  return Vertex(cc.getX() + sTCL, cc.getY() + sTCL, cc.getZ() - sTCL);
}

Vertex getVertex7(const Vertex& cc)
{
  return Vertex(cc.getX() - sTCL, cc.getY() + sTCL, cc.getZ() - sTCL);
}

Side::Side(const Vertex& _v0,
           const Vertex& _v1,
           const Vertex& _v2,
           const Vertex& _v3)
: v0(_v0), v1(_v1), v2(_v2), v3(_v3), c(0, 0, 0), which(sideCounter++)
{
  // Do nothing
}

Side::Side(const Vertex& cubeCenter, const FacePosition& whichFace)
: c(0, 0, 0), which(sideCounter++)
{
  switch (whichFace)
  {
    // 4, 0, 3, 7
    case left   : v0 = getVertex4(cubeCenter);
                  v1 = getVertex0(cubeCenter);
                  v2 = getVertex3(cubeCenter);
                  v3 = getVertex7(cubeCenter);
                  break;
    // 1, 5, 6, 2
    case right  : v0 = getVertex1(cubeCenter);
                  v1 = getVertex5(cubeCenter);
                  v2 = getVertex6(cubeCenter);
                  v3 = getVertex2(cubeCenter);
                  break;
    // 0, 1, 2, 3
    case front  : v0 = getVertex0(cubeCenter);
                  v1 = getVertex1(cubeCenter);
                  v2 = getVertex2(cubeCenter);
                  v3 = getVertex3(cubeCenter);
                  break;
    // 5, 4, 7, 6
    case back   : v0 = getVertex5(cubeCenter);
                  v1 = getVertex4(cubeCenter);
                  v2 = getVertex7(cubeCenter);
                  v3 = getVertex6(cubeCenter);
                  break;
    // 3, 2, 6, 7
    case top    : v0 = getVertex3(cubeCenter);
                  v1 = getVertex2(cubeCenter);
                  v2 = getVertex6(cubeCenter);
                  v3 = getVertex7(cubeCenter);
                  break;
    // 4, 5, 1, 0
    case bottom : v0 = getVertex4(cubeCenter);
                  v1 = getVertex5(cubeCenter);
                  v2 = getVertex1(cubeCenter);
                  v3 = getVertex0(cubeCenter);
                  break;
  }
}

const Color& Side::getColor() const
{
  return c;
}

void Side::setColor(const Color& color)
{
  c = color;
}


// Angle is counterclockwise
void Side::rotate(const Plane& plane, const Vertex& axis, GLdouble radians)
{
  v0.rotate(plane, axis, radians);
  v1.rotate(plane, axis, radians);
  v2.rotate(plane, axis, radians);
  v3.rotate(plane, axis, radians);
}

void Side::draw()
{
  glLoadName(which);
  glBegin(GL_QUADS);
    glColor3d(c.getR(), c.getG(), c.getB());
    if (which == selectedSide)
    {
      glColor3d(0, 0, 0);
    }
    glVertex3d(v0.getX(), v0.getY(), v0.getZ());
    glVertex3d(v1.getX(), v1.getY(), v1.getZ());
    glVertex3d(v2.getX(), v2.getY(), v2.getZ());
    glVertex3d(v3.getX(), v3.getY(), v3.getZ());
  glEnd();
}
