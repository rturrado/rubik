#ifndef COORD_HPP
#define COORD_HPP

#include "Constants.hpp"
#include "Plane.hpp"
#include "Vertex.hpp"

namespace Rubik {
namespace Graphics {

// Coordinates relative to the Rubik cube
//
// E.g.: left slice
//
// (0,0,0)   (0,0,1)   (0,0,2)
// (0,1,0)   (0,1,1)   (0,1,2)
// (0,2,0)   (0,2,1)   (0,2,2)

class Coord
{
  unsigned int x;
  unsigned int y;
  unsigned int z;
public:
  Coord(unsigned int, unsigned int, unsigned int);
  inline
  unsigned int serialize() const
  {
    return numberOfCubesPerSide     * x +
           numberOfCubesPerSideLine * y +
           z;
  }
  Vertex toVertex() const;
  void rotate(const Plane&, bool);
};

} // namespace Graphics 
} // namespace Rubik

#endif // ifndef COORD_HPP
