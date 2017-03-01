#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "opengl.h"
#include <fstream>
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scanningFinished = false;
    count = 0;
    capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, 400);

    tmr = new QTimer(this);
    connect(tmr, SIGNAL(timeout()), this, SLOT(process()));
}

void MainWindow::process()
{
    cv::Mat erodeElement = cv::getStructuringElement( cv::MORPH_RECT,cv::Size(3,3));
    cv::Mat dilateElement = cv::getStructuringElement( cv::MORPH_RECT,cv::Size(4,4));
    cv::Mat camera, imHSV;

    capture.read(camera);


    if(camera.empty())
    {
        scanningFinished = true;
        tmr->stop();
//        processFrames();
        return;
    }

    if(camera.empty())
    {
        return;
    }
    cv::cvtColor(camera,imHSV,cv::COLOR_BGR2HSV);
    cv::inRange(imHSV,cv::Scalar(ui->horizontalSlider_2->tickPosition(),ui->horizontalSlider_3->tickPosition(),ui->horizontalSlider->tickPosition()),cv::Scalar(ui->horizontalSlider_8->tickPosition(),ui->horizontalSlider_7->tickPosition(),ui->horizontalSlider_6->tickPosition()),imHSV);

    erode(imHSV,imHSV,erodeElement);
    erode(imHSV,imHSV,erodeElement);
    dilate(imHSV,imHSV,dilateElement);
    dilate(imHSV,imHSV,dilateElement);

    for(int i = 0; i < 640; ++i)
    {
        for(int j = 0; j < 400; j++)
        {
            int intensity = (int)imHSV.at<uchar>(j,i);
            frames1[count][j] = 0;
            if(intensity == 255)
            {
                 frames1[count][j] = i;
            }
        }
     }

    cv::cvtColor(camera, camera, CV_BGR2RGB);
    QImage qtest((uchar*)camera.data, camera.cols, camera.rows, camera.step, QImage::Format_RGB888);
    QImage qhsv((uchar*)imHSV.data, imHSV.cols, imHSV.rows, imHSV.step, QImage::Format_Indexed8);

    ui->label->setPixmap(QPixmap::fromImage(qtest).scaled(320, 240));
    ui->label_2->setPixmap(QPixmap::fromImage(qhsv).scaled(320, 240));
    count++;
}

void MainWindow::processFrames()
{
    std::cout << "Ovde processFrame";
    std::vector<double> TestX, TestY, TestZ;
    int points = 0;
    float PI = 3.141592;
    int camAngle = 15;

    ui->actionLabel->setText("Saving data to file");
    std::ofstream filesave("point.ply");
    filesave << "ply" << std::endl << "format ascii 1.0" << std::endl << "element vertex " << points << std::endl << "property float x" << std::endl << "property float y" << std::endl << "property float z" << std::endl << "end_header" << std::endl;


    for(int i = 0; i < 60; ++i)
    {
        for(int j = 0; j < 640; j++)
        {
            if(frames1[i][j] > 0)
            {
                double dist = 0;
                double x,y, z2;

                dist = ((double)300 - (double)frames1[i][j])/sin((double)15 * PI / 180.0);
                if ((float)dist > 0) {
                    z2 = (double)j - abs(((double)dist * tan((double)(ui->horizontalSlider_5->value())  * PI / 180.0)));
                }
                else {
                    z2 = (double)j + abs(((double)dist * tan((double)(ui->horizontalSlider_5->value())* PI / 180.0)));
                }
                x = dist*sin((double)(360.0/(double)60*(double)i) * PI / 180.0);
                y = dist*cos((double)(360.0/(double)60*(double)i) * PI / 180.0);

                this->points.x = x;
                this->points.y = y;
                this->points.z = z2;
                //Points.push_back(this->points);
                TestX.push_back(x);
                TestY.push_back(y);
                TestZ.push_back(z2);
                points++;
                filesave << x << " " << y << " " << z2 << std::endl;
            }
        }
    }
    ui->actionLabel->setText("Scanning Completed!");
    //OpenGl* gl = new OpenGl(TestX, TestY, TestZ);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->pushButton_2->setEnabled(false);
    tmr->start(33);
    ui->actionLabel->setText("Started Scanning!");
}

void MainWindow::on_pushButton_clicked()
{
    //QString fileName = QFileDialog::getOpenFileName(this, tr("Open Video"), "", tr("Video Files (*.avi)"));

    //capture.open(fileName.toStdString());
    capture.release();
    capture.open(0);
    ui->pushButton_2->setEnabled(true);
    ui->actionLabel->setText("Video Loaded!");
}
