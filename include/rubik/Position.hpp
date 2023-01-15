#ifndef POSITION_HPP
#define POSITION_HPP

#include <boost/shared_ptr.hpp>
#include "Coord.hpp"
#include "Cube.hpp"

namespace Rubik {
namespace Graphics {

const unsigned int numberOfPositions = numberOfCubes;

class Position;
typedef boost::shared_ptr<Position> PositionPtr;

class Position
{
  static PositionPtr positions[numberOfPositions];
  Coord coord;
  CubePtr cube;
  Position();
  Position(const Coord&);
  Position(const Position&);
  const Position& operator=(const Position&);
public:
  static const PositionPtr getPosition(const Coord&);
  static const PositionPtr getPosition(unsigned int);
  const Coord& getCoord() const;
  const CubePtr getCube() const;
  void setCube(const CubePtr);
  ~Position();
};

} // namespace Graphics 
} // namespace Rubik

#endif // ifndef POSITION_HPP
