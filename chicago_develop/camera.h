#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>

#include <QVector3D>

#include "matrix.h"

class Camera
{
    public:
        Camera() = default;
        Camera(QVector3D specificPosition, QVector3D specificDirection,
        QVector3D specificRight, QVector3D specificUp);

        void setPosition(QVector3D specificPosition){position = specificPosition;};

        QVector3D getPosition(){return position;};

        Matrix getLookAt();
        Matrix getMatrixRotateX(double angle);
        Matrix getMatrixRotateY(double angle);
        Matrix getMatrixRotateZ(double angle);

    private:
        QVector3D position;
        QVector3D direction;
        QVector3D right;
        QVector3D up;
};

#endif // CAMERA_H
