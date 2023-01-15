#ifndef FACE_POSITION_HPP
#define FACE_POSITION_HPP

#include "Plane.hpp"

namespace Rubik {
namespace Graphics {

enum FacePosition { left, right, bottom, top, back, front };

const unsigned int facePositionBegin = left;
const unsigned int facePositionEnd   = front;

FacePosition& rotateFacePosition(FacePosition&, const Plane&, bool);

} // namespace Graphics 
} // namespace Rubik

#endif // ifndef FACE_POSITION_HPP
