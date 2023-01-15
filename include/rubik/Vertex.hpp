#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <boost/shared_ptr.hpp>
#include <GL/gl.h>
#include <vector>
#include "Plane.hpp"

namespace Rubik {
namespace Graphics {

class Vertex;
typedef boost::shared_ptr<Vertex> VertexPtr;
typedef std::vector<VertexPtr> VectorVertexPtr;

class Vertex
{
  GLdouble x;
  GLdouble y;
  GLdouble z;
public:
  Vertex();
  Vertex(GLdouble xCoord, GLdouble yCoord, GLdouble zCoord);
  GLdouble getX() const;
  GLdouble getY() const;
  GLdouble getZ() const;
  void setX(GLdouble newX);
  void setY(GLdouble newY);
  void setZ(GLdouble newZ);
  void rotate(const Plane&, const Vertex&, GLdouble);
};

} // namespace Graphics 
} // namespace Rubik

#endif // ifndef VERTEX_HPP
