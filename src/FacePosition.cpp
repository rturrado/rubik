#include "FacePosition.hpp"

using namespace Rubik::Graphics;

FacePosition& rotateFacePositionX(FacePosition& f, bool clockwise)
{
  switch (f)
  {
    case bottom: f = clockwise ? front  : back;
                 break;
    case front:  f = clockwise ? top    : bottom;
                 break;
    case top:    f = clockwise ? back   : front;
                 break;
    case back:   f = clockwise ? bottom : top;
                 break;
    default:     break;
  }
  return f;
}

FacePosition& rotateFacePositionY(FacePosition& f, bool clockwise)
{
  switch (f)
  {
    case left:  f = clockwise ? back  : front;
                break;
    case back:  f = clockwise ? right : left;
                break;
    case right: f = clockwise ? front : back;
                break;
    case front: f = clockwise ? left  : right;
                break;
    default:    break;
  }
  return f;
}

FacePosition& rotateFacePositionZ(FacePosition& f, bool clockwise)
{
  switch (f)
  {
    case left:   f = clockwise ? top    : bottom;
                 break;
    case top:    f = clockwise ? right  : left;
                 break;
    case right:  f = clockwise ? bottom : top;
                 break;
    case bottom: f = clockwise ? left   : right;
                 break;
    default:     break;
  }
  return f;
}

namespace Rubik {
namespace Graphics {

FacePosition& rotateFacePosition(FacePosition& f,
                                 const Plane& plane,
                                 bool clockwise)
{
  switch (plane)
  {
    case x: return rotateFacePositionX(f, clockwise);
    case y: return rotateFacePositionY(f, clockwise);
    case z: return rotateFacePositionZ(f, clockwise);
  }
  return f;
}

} // namespace Graphics 
} // namespace Rubik
