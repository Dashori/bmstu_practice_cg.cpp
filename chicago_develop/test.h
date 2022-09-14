#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QtTest/QtTest>

#include "triangle.h"

class TestTriangle : public QObject
{
    Q_OBJECT

    public:
        explicit TestTriangle(QObject *parent = nullptr);

    private slots:
        void test_findZ();

};

#endif // TEST_H
