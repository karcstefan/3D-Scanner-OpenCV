#include "mainwindow.h"
#include <gl/glew.h>
#include <gl/glut.h>
#include <QApplication>

int main(int argc, char *argv[])
{
glutInit(&argc, argv);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
