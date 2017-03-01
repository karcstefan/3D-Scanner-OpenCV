#-------------------------------------------------
#
# Project created by QtCreator 2014-08-19T13:43:06
#
#-------------------------------------------------
q
QT       += core gui opengl webkit webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCV
TEMPLATE = app

INCLUDEPATH += D:\\opencv\\build\\include\\

LIBS += D:\\opencv\\build\\x86\\vc10\\lib\\opencv_core246d.lib
LIBS += D:\\opencv\\build\\x86\\vc10\\lib\\opencv_imgproc246d.lib
LIBS += D:\\opencv\\build\\x86\\vc10\\lib\\opencv_highgui246d.lib
LIBS += D:\\opencv\\build\\x86\\vc10\\lib\\opencv_ml246d.lib
LIBS += D:\\opencv\\build\\x86\\vc10\\lib\\opencv_video246d.lib
LIBS += D:\\opencv\\build\\x86\\vc10\\lib\\opencv_calib3d246d.lib
LIBS += D:\\opencv\\build\\x86\\vc10\\lib\\opencv_objdetect246d.lib
LIBS += D:\\opencv\\build\\x86\\vc10\\lib\\opencv_contrib246d.lib
LIBS += D:\\opencv\\build\\x86\\vc10\\lib\\opencv_flann246d.lib
LIBS += D:\\opencv\\build\\x86\\vc10\\lib\\opencv_nonfree246d.lib


INCLUDEPATH += D:\\opengl\\glew-1.11.0\\include
INCLUDEPATH += D:\\opengl\\freeglut\\include

LIBS += D:\\opengl\\glew-1.11.0\\lib\\Release\\Win32\\glew32.lib
LIBS += D:\\opengl\\freeglut\\lib\\freeglut.lib

SOURCES += main.cpp\
        mainwindow.cpp \
    opengl.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    opengl.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui
