#ifndef OPENGL_H
#define OPENGL_H
#include <gl/glew.h>
#include <gl/glut.h>
#include "mainwindow.h"
 struct pt{float x, y, z;};
class OpenGl
{
public:
    OpenGl(std::vector<double> x, std::vector<double> y, std::vector<double> z);
};

#endif // OPENGL_H
