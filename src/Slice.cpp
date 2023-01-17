#include <boost/thread.hpp>
#include <GL/gl.h>
#include <iostream>
#include "Frames.hpp"
#include "Position.hpp"
#include "Slice.hpp"
#include "Utility.hpp"

using namespace Rubik::Graphics;

SlicePtr Slice::slices[numberOfSlices];

// E.g.: left slices
// Plane = x
// which = 0, 1, and 2
//
// 6 7 8   15 16 17   24 25 26
// 3 4 5   12 13 14   21 22 23
// 0 1 2    9 10 11   18 19 20

Slice::Slice(const Plane& p, unsigned int w)
: plane(p), which(w), center(0, 0, 0)
{
  // center
  switch (plane)
  {
    case x: center.setX(Coord(which, 0, 0).toVertex().getX());
            break;
    case y: center.setY(Coord(0, which, 0).toVertex().getY());
            break;
    case z: center.setZ(Coord(0, 0, which).toVertex().getZ());
            break;
  }
  // positions
  for (unsigned int i = 0; i < numberOfCubesPerSide; i++)
  {
    unsigned int index;
    switch (plane)
    {
      case x:  index = i + which * numberOfCubesPerSide;
               break;
      case y:  index = i % numberOfCubesPerSideLine + \
                       (i / numberOfCubesPerSideLine) * numberOfCubesPerSide + \
                       which * numberOfCubesPerSideLine;
               break;
      case z:  index = i * numberOfCubesPerSideLine + which;
               break;
      default: break;
    }
    positions[i] = Position::getPosition(index);
  }
}

const SlicePtr Slice::getSlice(const Plane& plane, unsigned int which)
{
  // E.g.: x0, x1, x2, y0, y1, y2, z0, z1, z2
  unsigned int index = plane * numberOfCubesPerSideLine + which;
  if (slices[index] == 0)
  {
    slices[index] = SlicePtr(new Slice(plane, which));
  }
  return slices[index];
}

const PositionPtr Slice::getPosition(unsigned int i) const
{
  return positions[i];
}

// It does a 90º rotation,
// on the slice plane,
// and around the central cube
void Slice::rotate(bool clockwise = true)
{
  unsigned int startAngle = 0;
  unsigned int endAngle   = 90;
  for (unsigned int angle = startAngle; angle < endAngle; angle++)
  {
    std::cout << "Slice::rotate: angle: " << angle << std::endl;
    for (unsigned int i = 0; i < numberOfCubesPerSide; i++)
    {
      std::cout << "Slice::rotate: rotating cube: " << i << std::endl;
      PositionPtr positionPtr(getPosition(i));
      CubePtr cubePtr(positionPtr->getCube());
      GLdouble radians = clockwise ? -pi/180 : pi/180;
      cubePtr->rotate(plane, center, radians);
    }
    boost::this_thread::sleep(boost::posix_time::milliseconds(msBetweenFrames/10));
  }
  // Update cubes' coords and sides
  for (unsigned int i = 0; i < numberOfCubesPerSide; i++)
  {
    PositionPtr positionPtr(getPosition(i));
    CubePtr cubePtr(positionPtr->getCube());
    cubePtr->rotated(plane, clockwise);
    Cube::setCube(cubePtr);
  }
  // Update positions pointing to new cubes
  for (unsigned int i = 0; i < numberOfCubesPerSide; i++)
  {
    PositionPtr positionPtr(getPosition(i));
    Coord coord(positionPtr->getCoord());
    CubePtr cubePtr(Cube::getCube(coord));
    positionPtr->setCube(cubePtr);
  }
}

Slice::~Slice()
{
  // Do nothing
}
