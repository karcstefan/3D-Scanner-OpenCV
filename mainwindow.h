#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv\highgui.h>
#include <QDebug>
#include <opencv\cv.h>
#include <fstream>
#include <QImage>
#include <QTimer>
#include <QPixmap>
#include <vector>
#include <QFileDialog>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    cv::VideoCapture capture;
    struct pt{float x, y, z;} points;
    int count;
    int frames1[60][640];
    std::vector<std::vector<int>> frames;
    std::vector<pt> Points;

    QTimer* tmr;
    void processFrames();
    bool scanningFinished;
public slots:
    void process();
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
