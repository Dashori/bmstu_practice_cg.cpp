#ifndef SCENE_H
#define SCENE_H

#include <cstdlib>
#include <iostream>
#include <memory>
#include <math.h>

#include <QImage>
#include <QVector3D>
#include <QVector4D>

#include "ui_mainwindow.h"
#include "light.h"
#include "triangle.h"
#include "camera.h"
#include "loader.h"

class Scene
{
    public:
        Scene() = default;
        Scene(size_t width, size_t height) {canvasWidth = width; canvasHeight = height;};

        void setLoader(Loader specificLoader) {sceneLoader = specificLoader;};
        std::shared_ptr<std::ifstream> getLoaderFile(){return sceneLoader.getFile();};
        int loadScene(std::string filename);

        void setEyePosition(QVector3D specificPosition) {eyePosition = specificPosition;};
        QVector3D getEyePosition(){return eyePosition;};

        void addFace(Triangle specificFace) {faces.push_back(specificFace);};
        void addLight(Light specificLight) {lights.push_back(specificLight);};

        int getCountFaces(){return faces.size();};

        void initializedImage() {image = std::make_shared<QImage>(canvasWidth, canvasHeight, QImage::Format_RGB32);};
        void setImage(std::shared_ptr<QImage> specificImage) {image = specificImage;}
        std::shared_ptr<QImage>  getImage() {return image;};

        int isInside(QVector3D pointA, QVector3D pointB, QVector3D pointC, QVector3D point);

        int checkShadowBuffer(QVector3D point, size_t figureNumber, size_t faceNumber, Triangle face);

        void findIntensity(QVector3D point, QVector3D normal, double &diffuseIntensity, double &specIntensity);
        QColor findNewColor(QVector3D point, QVector3D normal, QColor color);

        void drawLights();

        void drawFaces();
        void zBufferFace(Triangle specificFace, size_t faceNumber);
        int checkShadowBuf(QVector3D point, Triangle specificFace, size_t faceNumber);

        void rotateX(double angle);
        void rotateY(double angle);
        void rotateZ(double angle);

    private:
        Loader sceneLoader;

        size_t canvasWidth = 1800;
        size_t canvasHeight = 1800;

        QVector3D eyePosition = QVector3D(500, 300, 0);
        Camera cam;

        std::shared_ptr<QImage> image;

        std::vector<Triangle> faces;
        std::vector<Light> lights;

        std::vector<std::vector<double>> depthBuffer;  // буфер z
        std::vector<std::vector<QColor>> colorBuffer;  // буфер кадра
};


#endif //SCENE_H
