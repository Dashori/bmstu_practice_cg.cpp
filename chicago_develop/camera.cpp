#include "camera.h"

Camera::Camera(QVector3D specificPosition, QVector3D specificDirection,
               QVector3D specificRight, QVector3D specificUp)
    :position(specificPosition),
     direction(specificDirection),
     right(specificRight),
     up(specificUp)
{

}


Matrix Camera::getLookAt()
{
    Matrix lookAt(4, 4);
    Matrix rotate(4, 4);
    Matrix move(4, 4);

    rotate.setELement(3, 3, 1);

    move.setELement(0, 0, 1);
    move.setELement(1, 1, 1);
    move.setELement(2, 2, 1);
    move.setELement(3, 3, 1);

    for (int i = 0; i < 3; i++)
    {
        rotate.setELement(0, i, right[i]);
        rotate.setELement(1, i, up[i]);
        rotate.setELement(2, i, direction[i]);
        move.setELement(i, 3, -position[i]);
    }

    rotate.printMatrix();
    move.printMatrix();

    lookAt = multiplicationMatrix(rotate, move);

    return lookAt;
}


Matrix Camera::getMatrixRotateX(double angle)
{
    double angleRad = angle * M_PI / 180;

    Matrix result(4, 4);
    result.setELement(1, 1, cos(angleRad));
    result.setELement(1, 2, -sin(angleRad));
    result.setELement(2, 1, sin(angleRad));
    result.setELement(2, 2, cos(angleRad));

    result.setELement(0, 0, 1);
    result.setELement(3, 3, 1);

    return result;
}


Matrix Camera::getMatrixRotateY(double angle)
{
    double angleRad = angle * M_PI / 180;

    Matrix result(4, 4);
    result.setELement(0, 0, cos(angleRad));
    result.setELement(2, 2, cos(angleRad));
    result.setELement(0, 2, sin(angleRad));
    result.setELement(2, 0, -sin(angleRad));

    result.setELement(1, 1, 1);
    result.setELement(3, 3, 1);

    return result;
}


Matrix Camera::getMatrixRotateZ(double angle)
{
    double angleRad = angle * M_PI / 180;

    Matrix result(4, 4);
    result.setELement(0, 0, cos(angleRad));
    result.setELement(1, 1, cos(angleRad));
    result.setELement(0, 1, -sin(angleRad));
    result.setELement(1, 0, -sin(angleRad));

    result.setELement(2, 2, 1);
    result.setELement(3, 3, 1);

    return result;
}
