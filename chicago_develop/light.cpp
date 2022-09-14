#include "light.h"

QVector3D Light::basePoint(double a, double b, double c, double d)
{
    double t = -(a * view.x() + b * view.y() + c * view.z() + d) / (a * a + b * b + c * c);
    double x = a * t + view.x();
    double y = b * t + view.y();
    double z = c * t + view.z();

    return QVector3D(x, y, z);
}

