#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <string>

#include <QMainWindow>
#include <QApplication>
#include <QFileDialog>
#include <QPixmap>
#include <QPainter>

#include "loader.h"
#include "scene.h"
#include "test.h"

#define EXIT_PROGRAM 1


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void setImageFlag(std::string specificFilename)
    {
        imageFlag = 1;
        outputFilename = specificFilename;
    };

    void setScene(std::string specificFilename);
    void setInputFilename(std::string specificFilename){inputFilename = specificFilename;}
    bool getInputFilename(){return inputFilename.empty();};

    int getSceneCountFaces(){return scene.getCountFaces();};

    void getImage();

    void on_rotateX_clicked();
    void on_rotateY_clicked();
    void on_rotateZ_clicked();

public slots:
    void on_load_clicked();
    void on_draw_clicked();

private:
    Ui::MainWindow *ui;

    int imageFlag = 0;
    std::string outputFilename;

    std::string inputFilename;

    Scene scene;
};
#endif // MAINWINDOW_H
