#include "opengl.h"
#include <iostream>
std::vector<double> xv,yv,zv;
int i,j;
float angle = 0.0f;
float lx=0.0f,lz=-1.0f;
float x=0.0f, z=0.5f;
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

void changeSize(int w, int h)
{
    if (h == 0)
        h = 1;

    float ratio =  w * 1.0 / h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void computePos(float deltaMove)
{

    x += deltaMove * lx * 0.1f;
    z += deltaMove * lz * 0.1f;
}

void renderScene(void)
{

    if (deltaMove)
    {
        computePos(deltaMove);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Kamera
    gluLookAt(	x, 0.1f, z, x+lx, 1.0f,  z+lz-5.2f, 0.0f, 1.0f,  0.1f );
    std::cout << x << " " << z << std::endl;

// Iscrtuvanje

    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_POINTS);

        for(int a = 0; a < xv.size(); a++)
        {
            glVertex3f (xv[a]/360, yv[a]/360, zv[a]/360);
        }

    glEnd();
    glutSwapBuffers();
}

void pressKey(int key, int xx, int yy)
{
       switch (key)
       {
             case GLUT_KEY_UP : deltaMove = 0.5f; break;
             case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
       }
}

void releaseKey(int key, int x, int y)
{

        switch (key)
        {
             case GLUT_KEY_UP :
             case GLUT_KEY_DOWN : deltaMove = 0;break;
        }
}

void mouseMove(int x, int y)
{
    if (xOrigin >= 0)
    {
        deltaAngle = (x - xOrigin) * 0.001f;

        lx = sin(angle + deltaAngle);
        lz = -cos(angle + deltaAngle);
    }
}

void mouseButton(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_UP) {
            angle += deltaAngle;
            xOrigin = -1;
        }
        else
        {
            xOrigin = x;
        }
    }
}
OpenGl::OpenGl(std::vector<double> x1, std::vector<double> y2, std::vector<double> z2)
{
    xv = x1; yv = y2; zv = z2;
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,600);
    glutCreateWindow("Point Cloud Viewer");
    glutDisplayFunc(renderScene);
        glutReshapeFunc(changeSize);
        glutIdleFunc(renderScene);

        glutIgnoreKeyRepeat(1);
        glutSpecialFunc(pressKey);
        glutSpecialUpFunc(releaseKey);

        // Registriranje na dvizenje i klik
        glutMouseFunc(mouseButton);
        glutMotionFunc(mouseMove);

        // Zapocnuvanje so ciklusot
        glEnable(GL_DEPTH_TEST);
        glutMainLoop();
}

