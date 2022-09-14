#include "triangle.h"

Triangle::Triangle(QVector3D specificPointA, QVector3D specificPointB, QVector3D specificPointC)
     :pointA(specificPointA),
      pointB(specificPointB),
      pointC(specificPointC)
{
    findCoefficients();
    findNormal();

}


Triangle::Triangle(QVector3D specificPointA, QVector3D specificPointB, QVector3D specificPointC, QColor specificColor)
     :pointA(specificPointA),
      pointB(specificPointB),
      pointC(specificPointC),
      color(specificColor)
{
    findCoefficients();
    findNormal();
}


void Triangle::findNormal()
{
    normal = QVector3D(a, b, c);
}


void Triangle::findCoefficients()
{
    a = 0, b = 0, c = 0, d = 0;

    std::vector<QVector3D> points;

    points.push_back(pointA);
    points.push_back(pointB);
    points.push_back(pointC);

    for (int i = 0; i < 3; i++)
    {
       int j = i + 1;

       if (i == 2)
          j = 0;

       a += (points[i][1] - points[j][1])*(points[i][2] + points[j][2]);
       b += (points[i][2] - points[j][2])*(points[i][0] + points[j][0]);
       c += (points[i][0] - points[j][0])*(points[i][1] + points[j][1]);
    }

    d = a * points[0][0] + b * points[0][1] + c * points[0][2];
    d *= -1;
}


std::tuple<double, double, double, double> Triangle::getCoefficients()
{
    std::tuple<double, double, double, double> coefficients = {a,b,c,d};

    return coefficients;
}


double Triangle::findZ(QVector3D point)
{
    double x = point.x();
    double y = point.y();

    if (c == 0)
        return 0;

    double z = -(a * x + b * y + d) / c;

    return z;
}
