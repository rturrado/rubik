#ifndef FACE_HPP
#define FACE_HPP

#include <boost/shared_ptr.hpp>
#include "Constants.hpp"
#include "FacePosition.hpp"
#include "Slice.hpp"

namespace Rubik {
namespace Graphics {

class Face;
typedef boost::shared_ptr<Face> FacePtr;

class Face 
{
  static FacePtr faces[numberOfFaces];
  SlicePtr slicePtr;
  FacePosition which;
  Face();
  Face(const Face&);
  Face(const FacePosition&);
  const Face& operator=(const Face&);
public:
  static const FacePtr getFace(const FacePosition&);
  const SlicePtr getSlice() const;
  ~Face();
};

} // namespace Graphics 
} // namespace Rubik

#endif // ifndef FACE_HPP
