#include "Position.hpp"

using namespace Rubik::Graphics;

/*static*/
PositionPtr Position::positions[numberOfPositions];

/*static*/
const PositionPtr Position::getPosition(const Coord& coord)
{
  unsigned int i = coord.serialize();
  if (positions[i] == 0)
  {
    positions[i] = PositionPtr(new Position(coord));
  }
  return positions[i];
}

Position::Position(const Coord& c)
: coord(c)
{
  // Do nothing
}

Position::~Position()
{
  // Do nothing
}

const PositionPtr Position::getPosition(unsigned int i)
{
  return positions[i];
}

const Coord& Position::getCoord() const
{
  return coord;
}

const CubePtr Position::getCube() const
{
  return cube;
}

void Position::setCube(const CubePtr c)
{
  cube = c;
}
