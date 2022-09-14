#include "test.h"

TestTriangle::TestTriangle(QObject *parent)
    :QObject{parent}
{

}


void TestTriangle::test_findZ()
{
    Triangle polygon(QVector3D(0, 0, 10), QVector3D(10, 10, 10), QVector3D(10, 0, 10));

    double z = polygon.findZ(QVector3D(6, 6, 0));

    QCOMPARE(z, 10);
}
