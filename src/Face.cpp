#include "Face.hpp"
#include "Slice.hpp"

using namespace Rubik::Graphics;

FacePtr Face::faces[numberOfFaces];

Face::Face(const FacePosition& _which)
: which(_which)
{
  switch (which)
  {
    case left:   slicePtr = Slice::getSlice(x, indexOfFirstSlice);
                 break;
    case right:  slicePtr = Slice::getSlice(x, indexOfLastSlice);
                 break;
    case bottom: slicePtr = Slice::getSlice(y, indexOfFirstSlice);
                 break;
    case top:    slicePtr = Slice::getSlice(y, indexOfLastSlice);
                 break;
    case back:   slicePtr = Slice::getSlice(z, indexOfFirstSlice);
                 break;
    case front:  slicePtr = Slice::getSlice(z, indexOfLastSlice);
                 break;
    default:     break;
  }
}

const FacePtr Face::getFace(const FacePosition& which)
{
  if (faces[which] == 0)
  {
    faces[which] = FacePtr(new Face(which));
  }
  return faces[which];
}

const SlicePtr Face::getSlice() const
{
  return slicePtr;
}

Face::~Face()
{
  // Do nothing
}
