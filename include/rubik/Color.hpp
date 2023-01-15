#ifndef COLOR_HPP
#define COLOR_HPP

#include <GL/gl.h>

namespace Rubik {
namespace Graphics {

class Color 
{
  GLdouble r; // red
  GLdouble g; // green
  GLdouble b; // blue
  GLdouble a; // alpha
public:
  Color(GLdouble, GLdouble, GLdouble, GLdouble alpha = 0.0);
  GLdouble getR() const;
  GLdouble getG() const;
  GLdouble getB() const;
  GLdouble getA() const;
  void setA(GLdouble);
};

} // namespace Graphics 
} // namespace Rubik

#endif // ifndef COLOR_HPP
