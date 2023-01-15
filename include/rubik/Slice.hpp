#ifndef SLICE_HPP
#define SLICE_HPP

#include <boost/shared_ptr.hpp>
#include "Constants.hpp"
#include "Plane.hpp"
#include "Position.hpp"
#include "Vertex.hpp"

namespace Rubik {
namespace Graphics {

class Slice;
typedef boost::shared_ptr<Slice> SlicePtr;

const unsigned int indexOfFirstSlice = 0;
const unsigned int indexOfLastSlice  = numberOfCubesPerSideLine - 1;

class Slice
{
  static SlicePtr slices[numberOfSlices];
  Plane plane; // x, y, or z
  unsigned int which; // which slice in that plane
  Vertex center;
  PositionPtr positions[numberOfCubesPerSide];
  Slice();
  Slice(const Slice&);
  Slice(const Plane&, unsigned int);
  const Slice& operator=(const Slice&);
public:
  static const SlicePtr getSlice(const Plane&, unsigned int);
  const PositionPtr getPosition(unsigned int) const;
  void rotate(bool);
  ~Slice();
};

} // namespace Graphics 
} // namespace Rubik

#endif // ifndef SLICE_HPP
