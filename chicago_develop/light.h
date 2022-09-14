#ifndef LIGHT_H
#define LIGHT_H

#include <cmath>

#include <QVector3D>

#include "triangle.h"

class Light
{
    public:
        Light() = default;
        Light(QVector3D specificView, double specificIntensity)
        {
            view = specificView;
            intensity = specificIntensity;
        };

        void setView(QVector3D specificView) {view = specificView;};
        QVector3D getView() {return view;};

        void setIntensity(double specificIntensity) {intensity = specificIntensity;};
        double getIntensity(){return intensity;};

        QVector3D basePoint(double a, double b, double c, double d);

    private:
        QVector3D view;
        double intensity;
};

#endif // LIGHT_H
