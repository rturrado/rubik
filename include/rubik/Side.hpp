#ifndef SIDE_HPP
#define SIDE_HPP

#include <boost/shared_ptr.hpp>
#include <GL/gl.h>
#include <map>
#include "Color.hpp"
#include "FacePosition.hpp"
#include "Plane.hpp"
#include "Vertex.hpp"

namespace Rubik {
namespace Graphics {

class Side;
typedef boost::shared_ptr<Side> SidePtr;
typedef std::map<FacePosition, SidePtr> MapSidePtr;

class Side
{
  static unsigned int sideCounter;
  static unsigned int selectedSide;
  Vertex v0;
  Vertex v1;
  Vertex v2;
  Vertex v3;
  Color c;
  unsigned int which;
  Side(const Vertex&, const Vertex&, const Vertex&, const Vertex&);
public:
  static void selectSide(unsigned int);
  Side(const Vertex&, const FacePosition&);
  const Color& getColor() const;
  void setColor(const Color& color);
  void rotate(const Plane&, const Vertex&, GLdouble);
  void draw();
};

} // namespace Graphics 
} // namespace Rubik

#endif // ifndef SIDE_HPP
