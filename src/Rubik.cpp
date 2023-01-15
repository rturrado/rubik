/*
 * Rubik.cpp - a Rubik cube
 *
 * Usage: set a rotation axis with rx, ry, or rz
 *        change the rotation factor on the selected axis with + or -
 */

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <ctime>
#include <vector>

#include "Color.hpp"
#include "Constants.hpp"
#include "Cube.hpp"
#include "Face.hpp"
#include "FacePosition.hpp"
#include "Frames.hpp"
#include "Position.hpp"
#include "Slice.hpp"
#include "Utility.hpp"
#include "Vertex.hpp"

using namespace Rubik::Graphics;
using namespace std;

// Window size
const int windowWidth  = 500;
const int windowHeight = 500;
// gluLookAt parameters
GLdouble eyeX = 0;
GLdouble eyeY = 2;
GLdouble eyeZ = 10;
GLdouble centerX = 0;
GLdouble centerY = 0;
GLdouble centerZ = 0;
GLdouble upX = 0;
GLdouble upY = 1;
GLdouble upZ = 0;
// gluPerspective parameters
GLdouble fovy  = 60;
GLdouble zNear = 1;
GLdouble zFar  = 100;
// Cubes' sides' colours
const Color blue   (0.0, 0.2, 0.8);
const Color green  (0.2, 0.6, 0.2);
const Color orange (0.8, 0.3, 0.4);
const Color red    (0.8, 0.2, 0.2);
const Color white  (1.0, 1.0, 1.0);
const Color yellow (0.9, 0.9, 0.1);
Color colors[6] = { blue, green, orange, red, white, yellow };
// Keyboard controls
GLdouble rotationFactor[3] = { 15.0, 45.0, 0.0 };
// Mouse
unsigned int xMouseOld = 0;
unsigned int yMouseOld = 0;
// Threads
boost::thread_group tG;
// Movements
const int numberOfMovements = 50;

void drawRubik()
{
  // Cubes
  for (int x = 0; x < numberOfCubesPerSideLine; x++)
  {
    for (int y = 0; y < numberOfCubesPerSideLine; y++)
    {
      for (int z = 0; z < numberOfCubesPerSideLine; z++)
      {
        PositionPtr positionPtr(Position::getPosition(Coord(x, y, z)));
        CubePtr cubePtr(positionPtr->getCube());
        cubePtr->draw();
      }
    }
  }
}

void display()
{
  // Fill the background in black
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Clear modelview
  glLoadIdentity();
  glRotated(rotationFactor[0], 1, 0, 0);
  glRotated(rotationFactor[1], 0, 1, 0);
  glRotated(rotationFactor[2], 0, 0, 1);
  drawRubik();

  glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
  static unsigned int axis = 0;

  switch (key)
  {
    case 27:  exit(1);
              break;
    case 'x': axis = 0;
              break;
    case 'y': axis = 1;
              break;
    case 'z': axis = 2;
              break;
    case '+': rotationFactor[axis] += 5;
              break;
    case '-': rotationFactor[axis] -= 5;
              break;
    default:  break;
  }
}

void processHits(GLint numberOfHits, GLuint *buffer)
{
  cout << "numberOfHits: " << numberOfHits << endl;

  GLuint numberOfNames;
  for (unsigned int i = 0; i < numberOfHits; i++)
  {
    numberOfNames = *buffer;
    cout << "number of names: " << *buffer++ << endl;
    cout << "min z          : " << *buffer++/0x7fffffff << endl;
    cout << "max z          : " << *buffer++/0x7fffffff << endl;
    cout << "names          :";
    for (unsigned int j = 0; j < numberOfNames; j++)
    {
      cout << " " << *buffer++;
    }
    cout << endl;
  }
}

void selection(int x, int y)
{
  GLuint buffer[512] = {0};
  GLint numberOfHits;
  GLint viewport[4];
 
  // Use buffer for selection
  glSelectBuffer(512, buffer);
  // Switch to selection mode
  glRenderMode(GL_SELECT);
  // Clear the name's stack
  glInitNames();
  // Push one element onto the stack
  glPushName(0);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
    glLoadIdentity();
    // Get viewport info
    glGetIntegerv(GL_VIEWPORT, viewport);
    // Restrict the drawing to an area around the cursor
    gluPickMatrix(x, y, 1, 1, viewport);
    gluPerspective(fovy, ((GLdouble) windowWidth) / windowHeight, zNear, zFar);
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
    // Draw the objects onto the screen
    glMatrixMode(GL_MODELVIEW);
    display();
    glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  // Get the number of objects drawn in that area
  // Return to render mode
  numberOfHits = glRenderMode(GL_RENDER);
  cout << "[selection] numberOfHits: " << numberOfHits << endl;
  processHits(numberOfHits, buffer);
  if (numberOfHits > 0)
  {
    cout << "[selection] evaluating hit 1" << endl;
    GLuint objectMinZ = buffer[1];
    GLuint objectName = buffer[3];
    cout << "minZ: " << objectMinZ << "\tname: " << objectName << endl;
    for (unsigned int i = 1; i < numberOfHits; i++)
    {
      cout << "[selection] evaluating hit: " << i+1 << endl;
      if (buffer[i*4+1] < objectMinZ)
      {
        objectMinZ = buffer[i*4+1];
        objectName = buffer[i*4+3];
        cout << "minZ: " << objectMinZ << "\tname: " << objectName << endl;
      }
    }
    cout << "[selection] objectName: " << objectName << endl;
    Side::selectSide(objectName);
  }
}

void mouse(int button, int state, int x, int y)
{ 
}

void passiveMotion(int x, int y)
{ 
  //if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
  //{
    cout << "[mouse] x: " << x << "\ty: " << y << endl;
    selection(x, windowHeight - y);
  //}
}

void timer(int value)
{
  if (value)
  {
    glutPostRedisplay();
  }
  glutTimerFunc(msBetweenFrames, timer, value);
}

void visibility(int state)
{
  switch (state)
  {
    case GLUT_VISIBLE:     timer(1);
                           break;
    case GLUT_NOT_VISIBLE: timer(0);
                           break;
    default:               break;
  }
}

void initCube()
{
  // Create positions and cubes, and
  // associate cubes to positions
  for (int x = 0; x < numberOfCubesPerSideLine; x++)
  {
    for (int y = 0; y < numberOfCubesPerSideLine; y++)
    {
      for (int z = 0; z < numberOfCubesPerSideLine; z++)
      {
        Coord coord(x, y, z);
        PositionPtr positionPtr(Position::getPosition(coord));
        CubePtr cubePtr(Cube::getCube(coord));
        positionPtr->setCube(cubePtr);
      }
    }
  }
  // Create sides
  // Walk all faces
  for (unsigned int whichFace = facePositionBegin;
       whichFace <= facePositionEnd;
       ++whichFace)
  {
    FacePosition facePosition = static_cast<FacePosition>(whichFace);
    FacePtr facePtr(Face::getFace(facePosition));
    SlicePtr slicePtr(facePtr->getSlice());
    // Get cubes in each face
    for (int i = 0; i < numberOfCubesPerSide; i++)
    {
      PositionPtr positionPtr(slicePtr->getPosition(i));
      CubePtr cubePtr(positionPtr->getCube());
      SidePtr sidePtr(cubePtr->getSide(facePosition));
      sidePtr->setColor(colors[facePosition]);
    }
  }
}

void initGraphics(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(windowWidth, windowHeight);
  glutCreateWindow("Rubik");

  initCube();

  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutPassiveMotionFunc(passiveMotion);
  glutTimerFunc(msBetweenFrames, timer, 1);
  glutVisibilityFunc(visibility);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fovy, ((GLdouble) windowWidth) / windowHeight, zNear, zFar);
  gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
}

void test1Thread()
{
  // Just a performance test
  while (true)
  {
    rotationFactor[0] += 5;
    rotationFactor[1] += 5;
    rotationFactor[2] += 5;
    boost::this_thread::sleep(boost::posix_time::milliseconds(10*msBetweenFrames));
  }
}

void test2Thread()
{
  for (unsigned int whichPlane = planeBegin;
       whichPlane <= planeEnd;
       whichPlane++)
  {
    Plane plane = static_cast<Plane>(whichPlane);
    bool clockwise = true;
    for (unsigned int which = 0;
         which < numberOfCubesPerSideLine;
         which++)
    {
      std::cout << "Rotating slice: " << which << std::endl;
      SlicePtr slicePtr(Slice::getSlice(plane, which));
      slicePtr->rotate(clockwise);
      clockwise = !clockwise;
    }
  }
}

void test3Thread()
{
  srand(time(NULL));
  for (unsigned int i = 0; i < numberOfMovements; i++)
  {
    unsigned int whichPlane = rand() % (planeEnd + 1);
    Plane plane = static_cast<Plane>(whichPlane);
    bool clockwise = (rand() % 2) != 0;
    unsigned int which = rand() % numberOfCubesPerSideLine;
    std::cout << "Rotating slice: " << which << std::endl;
    SlicePtr slicePtr(Slice::getSlice(plane, which));
    slicePtr->rotate(clockwise);
  }
}

void mainThread()
{
  // Rotate cube
  //tG.create_thread(boost::bind(test1Thread));
  // Rotate all the slices
  //tG.create_thread(boost::bind(test2Thread));
  // Scramble
  //tG.create_thread(boost::bind(test3Thread));
}

int main(int argc, char **argv)
{
  initGraphics(argc, argv);
  tG.create_thread(boost::bind(mainThread));
  glutMainLoop();

  tG.join_all();
  return 0;
}
