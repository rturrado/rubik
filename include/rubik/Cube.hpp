#ifndef CUBE_HPP
#define CUBE_HPP

#include <boost/shared_ptr.hpp>
#include <GL/gl.h>
#include "Constants.hpp"
#include "Coord.hpp"
#include "FacePosition.hpp"
#include "Side.hpp"
#include "Vertex.hpp"

namespace Rubik {
namespace Graphics {

class Cube;
typedef boost::shared_ptr<Cube> CubePtr;

class Cube
{
  static CubePtr cubes[numberOfCubes];
  Coord coord;
  Vertex center;
  MapSidePtr sides;
  Cube();
  Cube(const Coord&);
  Cube(const Cube&);
  const Cube& operator=(const Cube&);
public:
  static const CubePtr getCube(const Coord&);
  static void setCube(const CubePtr);
  const Coord& getCoord() const;
  const SidePtr getSide(const FacePosition&);
  void rotate(const Plane&, const Vertex&, GLdouble);
  void rotated(const Plane&, bool);
  void draw() const;
  ~Cube();
};

} // namespace Graphics 
} // namespace Rubik

#endif // ifndef CUBE_HPP
