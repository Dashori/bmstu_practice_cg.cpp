#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>
#include <QColor>

#include <cmath>

class Triangle
{
    public:
        Triangle() = default;

        Triangle(QVector3D specificPointA,
                 QVector3D specificPointB,
                 QVector3D specificPointC);

        Triangle(QVector3D specificPointA,
                 QVector3D specificPointB,
                 QVector3D specificPointC,
                 QColor    specificColor);

        std::vector<QVector3D> getPoints()
        {
            return std::vector<QVector3D>{pointA, pointB, pointC};
        };

        void setPoints(QVector3D specificA, QVector3D specificB, QVector3D specificC)
        {
            pointA = specificA;
            pointB = specificB;
            pointC = specificC;
        };

        void setA(QVector3D specificA) {pointA = specificA;};
        void setB(QVector3D specificB) {pointB = specificB;};
        void setC(QVector3D specificC) {pointC = specificC;};

        void findCoefficients();
        std::tuple<double, double, double, double> getCoefficients();

        void findNormal();
        QVector3D getNormal(){findCoefficients(); findNormal(); return normal;};

        double findZ(QVector3D point);

        QColor getColor(){return color;};
        void setColor(QColor specificColor){color = specificColor;};

    private:
        QVector3D pointA, pointB, pointC;

        QVector3D normal;

        double a, b, c, d; //plane

        QColor color;
};


#endif //TRIANGLE_H
