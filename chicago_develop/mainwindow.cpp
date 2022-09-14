#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setScene(std::string specificFilename)
{
    setInputFilename(specificFilename);

    Loader load;
    scene.setLoader(load);
    scene.loadScene(inputFilename);
    scene.addLight(Light(QVector3D(200, 300, 1200), 0.3));
    scene.initializedImage();
    scene.rotateY(-20);
}


void MainWindow::on_load_clicked()
{
    auto filename = QFileDialog::getOpenFileName();
    setInputFilename(filename.toStdString());

    Loader load;
    scene.setLoader(load);
    scene.loadScene(inputFilename);
    scene.addLight(Light(QVector3D(200, 300, 1200), 0.3));
    scene.initializedImage();
    scene.rotateY(-20);
}


void MainWindow::on_draw_clicked()
{
    if( getInputFilename() == true)
        return;

    scene.drawFaces();

    std::shared_ptr<QImage> currentImage = (scene.getImage());

    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->canvas->setScene(scene);

    QPixmap pixmap = QPixmap::fromImage(*currentImage);

    ui->canvas->scene()->addPixmap(pixmap);
}


void MainWindow::getImage()
{
    scene.drawFaces();

    std::shared_ptr<QImage> currentImage = (scene.getImage());

    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->canvas->setScene(scene);

    QPixmap pixmap = QPixmap::fromImage(*currentImage);

    currentImage->save(outputFilename.c_str(), "PNG");
}


void MainWindow::on_rotateX_clicked()
{
    scene.rotateX(-1);
    scene.drawFaces();

    std::shared_ptr<QImage> currentImage = (scene.getImage());

    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->canvas->setScene(scene);

    QPixmap pixmap = QPixmap::fromImage(*currentImage);
    ui->canvas->scene()->addPixmap(pixmap);
}


void MainWindow::on_rotateY_clicked()
{
    scene.rotateY(-3);
    scene.drawFaces();

    std::shared_ptr<QImage> currentImage = (scene.getImage());

    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->canvas->setScene(scene);

    QPixmap pixmap = QPixmap::fromImage(*currentImage);
    ui->canvas->scene()->addPixmap(pixmap);
}


void MainWindow::on_rotateZ_clicked()
{
    scene.rotateZ(-1);
    scene.drawFaces();

    std::shared_ptr<QImage> currentImage = (scene.getImage());

    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->canvas->setScene(scene);

    QPixmap pixmap = QPixmap::fromImage(*currentImage);
    ui->canvas->scene()->addPixmap(pixmap);
}
