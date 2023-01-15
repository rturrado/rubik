#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <GL/gl.h>

namespace Rubik {
namespace Graphics {

const unsigned int numberOfFaces            = 6;
const unsigned int nOF                      = 6;
// Should not be constant, but configurable
const unsigned int numberOfCubesPerSideLine = 3;
const unsigned int nOCPSL                   = numberOfCubesPerSideLine;
const unsigned int numberOfCubesPerSide     = nOCPSL * nOCPSL;
const unsigned int nOCPS                    = numberOfCubesPerSide;
const unsigned int numberOfCubes            = nOCPS * nOCPSL;
const unsigned int nOC                      = nOCPS * nOCPSL;
const unsigned int numberOfSides            = nOC * nOF;
// 3 dimensions
const unsigned int numberOfSlices           = nOCPSL * 3;
const GLdouble cubeSizeLength               = 1;
const GLdouble cubeSeparation               = 0.05;

} // namespace Graphics 
} // namespace Rubik

#endif // ifndef CONSTANTS_HPP
