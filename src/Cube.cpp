#include <iostream>
#include "Cube.hpp"
#include "FacePosition.hpp"

using namespace Rubik::Graphics;

/*static*/
CubePtr Cube::cubes[numberOfCubes];

/*static*/
const CubePtr Cube::getCube(const Coord& coord)
{
  unsigned int i = coord.serialize();
  if (cubes[i] == 0)
  {
    cubes[i] = CubePtr(new Cube(coord));
  }
  return cubes[i];
}

/*static*/
void Cube::setCube(const CubePtr cubePtr)
{
  // Update cubes
  Coord coord(cubePtr->getCoord());
  unsigned int i = coord.serialize();
  cubes[i] = cubePtr;
}

Cube::Cube(const Coord& c)
: coord(c), center(c.toVertex())
{
  // Initialize all sides to grey
  const Color grey (0.5, 0.5, 0.5);
  for (unsigned int whichFace = facePositionBegin;
       whichFace <= facePositionEnd;
       ++whichFace)
  {
    FacePosition facePosition = static_cast<FacePosition>(whichFace);
    SidePtr sidePtr(getSide(facePosition));
    sidePtr->setColor(grey);
  }
}

Cube::~Cube()
{
  // Do nothing
}

const Coord& Cube::getCoord() const
{
  return coord;
}

const SidePtr Cube::getSide(const FacePosition& whichFace)
{
  if (sides.find(whichFace) == sides.end())
  {
    sides[whichFace] = SidePtr(new Side(center, whichFace));
  }
  return sides[whichFace];
}

// Angle is counterclockwise
void Cube::rotate(const Plane& plane, const Vertex& axis, GLdouble radians)
{
  // Rotate center
  center.rotate(plane, axis, radians);

  // Rotate sides
  MapSidePtr::iterator it;
  for (it = sides.begin(); it != sides.end(); ++it)
  {
    SidePtr sidePtr = (*it).second;
    sidePtr->rotate(plane, axis, radians);
  }
}

// Update coord and sides after a 90º rotation
void Cube::rotated(const Plane& plane, bool clockwise)
{
  // Update coord
  coord.rotate(plane, clockwise);
  // Update sides
  MapSidePtr newSides;
  MapSidePtr::iterator it;
  for (it = sides.begin(); it != sides.end(); ++it)
  {
    FacePosition facePosition = (*it).first;
    SidePtr sidePtr = (*it).second;
    FacePosition newFacePosition =
      rotateFacePosition(facePosition, plane, clockwise);
    newSides[newFacePosition] = sidePtr;
  }
  sides = newSides;
}

void Cube::draw() const
{
  MapSidePtr::const_iterator cit;
  for (cit = sides.begin(); cit != sides.end(); ++cit)
  {
    SidePtr sidePtr = (*cit).second;
    sidePtr->draw();
  }
}
