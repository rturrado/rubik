#include <GL/gl.h>

#include "Color.hpp"

using namespace Rubik::Graphics;

Color::Color(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha)
: r(red), g(green), b(blue), a(alpha)
{
  // Do nothing
}

GLdouble Color::getR() const
{
  return r;
}

GLdouble Color::getG() const
{
  return g;
}

GLdouble Color::getB() const
{
  return b;
}

GLdouble Color::getA() const
{
  return a;
}

void Color::setA(GLdouble alpha)
{
  a = alpha;
}
