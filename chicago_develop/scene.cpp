#include "scene.h"

int Scene::loadScene(std::string filename)
{
    if (sceneLoader.checkFile(filename))
        return EXIT_FAILURE;

    faces = sceneLoader.readFaces();

    return EXIT_SUCCESS;
}


QColor getNewColor(QColor color, double diffuseIntensity, double spectralIntensity)
{
    auto newRed = color.red() * diffuseIntensity + 255 * spectralIntensity;
    auto newGreen = color.green() * diffuseIntensity + 255 * spectralIntensity;
    auto newBlue = color.blue() * diffuseIntensity + 255 * spectralIntensity;

    if (newRed > 255)
        newRed = 255;

    if (newBlue > 255)
        newBlue = 255;

    if (newGreen > 255)
        newGreen = 255;

    return QColor(newRed, newGreen, newBlue);
}


double scalarProduction(QVector3D v1, QVector3D v2)
{
    return QVector3D::dotProduct(v1, v2);
}


QVector3D getReflectVector(QVector3D viewVector, QVector3D normal)
{
  return normal * 2.0 * scalarProduction(viewVector, normal) - viewVector;
}


void Scene::findIntensity(QVector3D point, QVector3D normal, double &diffuseIntensity, double &spectralIntensity)
{
    diffuseIntensity = 0.0;
    spectralIntensity = 0.0;

    QVector3D direction = (eyePosition - point).normalized(); // направляющий вектор света, типо до камеры
    normal.normalize();

    for (size_t i = 0; i < lights.size(); i++)
    {
      QVector3D light = (lights[i].getView() - point).normalized(); // вектор до источника света
        {
          diffuseIntensity = 0.0;
          spectralIntensity = 0.0;

          QVector3D direction = (eyePosition - point).normalized(); // направляющий вектор света, типо до камеры
          normal.normalize();

          for (size_t i = 0; i < lights.size(); i++)
          {
            QVector3D light = (lights[i].getView() - point).normalized(); // вектор до источника света

            diffuseIntensity += lights[i].getIntensity() * std::max(0., scalarProduction(normal, light));

            QVector3D reflect = (getReflectVector(-direction, normal)).normalized();

            spectralIntensity += pow(std::max(0., scalarProduction(reflect, light)), 100)
                    * lights[i].getIntensity();
          }
      }


      diffuseIntensity += lights[i].getIntensity() * std::max(0., scalarProduction(normal, light));

      QVector3D reflect = (getReflectVector(-direction, normal)).normalized();

      spectralIntensity += pow(std::max(0., scalarProduction(reflect, light)), 100)
              * lights[i].getIntensity();
    }
}


QColor Scene::findNewColor(QVector3D point, QVector3D normal, QColor color)
{
    QColor newColor;
    double diffuseIntensity, spectralIntensity;

    findIntensity(point, normal, diffuseIntensity, spectralIntensity);
    newColor = getNewColor(color, diffuseIntensity, spectralIntensity);

    return newColor;
}


int Scene::isInside(QVector3D pointA, QVector3D pointB, QVector3D pointC, QVector3D point)
{
    double x = point.x();
    double y = point.y();

    double vector1 = (pointA.x() - x) * (pointB.y() - pointA.y());
    vector1 -= (pointB.x() - pointA.x()) * (pointA.y() - y);

    double vector2 = (pointB.x() - x) * (pointC.y() - pointB.y());
    vector2 -= (pointC.x() - pointB.x()) * (pointB.y() - y);

    double vector3 = (pointC.x() - x) * (pointA.y() - pointC.y());
    vector3 -= (pointA.x() - pointC.x()) * (pointC.y() - y);

    if (!(vector1 >= 0 && vector2 >= 0 && vector3 >= 0)
       && !(vector1 <= 0 && vector2 <= 0 && vector3 <= 0))
        return 0;

    return 1;
}


void Scene::drawLights()
{
    for(size_t i = 0; i < lights.size(); i++)
    {
        Light tempLight = lights[i];
        QVector3D tempView = tempLight.getView();

        for (size_t j = tempView[0]-2; j < tempView[0] + 2; j++)
            for (size_t k = tempView[1] - 2; k < tempView[1] + 2; k++)
                image->setPixel(j, k, qRgb(255, 165, 0));
    }

    for (auto i = eyePosition.x() ; i < eyePosition.x() + 2; i++)
        for (auto j = eyePosition.y(); j < eyePosition.y() + 2; j++)
            image->setPixel(i, j, qRgb(255, 0, 0));
}


int Scene::checkShadowBuf(QVector3D point, Triangle specificFace, size_t faceNumber)
{
    std::cout << "hate shadows";

    return 0;
}


void Scene::zBufferFace(Triangle specificFace, size_t faceNumber)
{
    std::vector<QVector3D> currentPoints = specificFace.getPoints();
    QVector3D normal = specificFace.getNormal();

    if (normal.z() < 0)
        normal.setZ(normal.z() * (-1));

    double xArray[3], yArray[3];

    for(size_t i = 0; i < 3; i++)
    {
        xArray[i] = currentPoints[i][0];
        yArray[i] = currentPoints[i][1];
    }

    int yMin = std::min(std::min(yArray[0], yArray[1]), yArray[2]);
    int yMax = std::max(std::max(yArray[0], yArray[1]), yArray[2]);

    int xMin = std::min(std::min(xArray[0], xArray[1]), xArray[2]);
    int xMax = std::max(std::max(xArray[0], xArray[1]), xArray[2]);

    for (int y = yMin; y < yMax; y++)
        for (int x = xMin; x < xMax; x++)
            {
                QVector3D point(x, y, 0);

                if (!isInside(currentPoints[0], currentPoints[1], currentPoints[2], point))
                {
                    continue;
                }
                else
                {
                    auto z = specificFace.findZ(point);

                    if (z >= depthBuffer[x][y])
                    {
                        //if (checkShadowBuf(point, specificFace, faceNumber))
                        //{
                            //colorBuffer[x][y] = QColor(0, 0, 0);
                        //}

                        depthBuffer[x][y] = z;
                        point.setZ(z);

                        QColor newColor = findNewColor(point, normal, specificFace.getColor());
                        colorBuffer[x][y] = newColor;
                    }
                }
            }
}


void Scene::drawFaces()
{
    depthBuffer.erase(depthBuffer.begin(), depthBuffer.end());
    colorBuffer.erase(colorBuffer.begin(), colorBuffer.end());

    for (size_t i = 0; i < canvasWidth; i++)
    {
        depthBuffer.push_back(std::vector<double>(canvasHeight, -5000));
        colorBuffer.push_back(std::vector<QColor>(canvasHeight, QColor(0, 0, 0)));
    }

    for (size_t i = 0; i < faces.size(); i++)
        zBufferFace(faces[i], i);

    for (size_t x = 0; x < canvasWidth; x++)
        for (size_t y = 0; y < canvasHeight; y++)
            image->setPixel(x, y, colorBuffer[x][y].rgb());
}


void Scene::rotateX(double angle)
{
    for (size_t i = 0; i < faces.size(); i++)
    {
        auto points = faces[i].getPoints();

        for (size_t j = 0; j < 3; j++)
        {
            QVector3D point = points[j];
            QVector4D tempPoint(point);
            Matrix tempMatrix(tempPoint);

            Matrix rotateX = cam.getMatrixRotateX(angle);

            Matrix result = multiplicationMatrix(tempMatrix, rotateX);

            int x = result.getElement(0, 0);
            int y = result.getElement(0, 1);
            int z = result.getElement(0, 2);

            if (j == 0)  // смешно, я знаю
                faces[i].setA(QVector3D(x,y,z));

            if (j == 1)
                faces[i].setB(QVector3D(x,y,z));

            if (j == 2)
                faces[i].setC(QVector3D(x,y,z));
        }
    }
}


void Scene::rotateY(double angle)
{
    for (size_t i = 0; i < faces.size(); i++)
    {
        auto points = faces[i].getPoints();

        for (size_t j = 0; j < 3; j++)
        {
            QVector3D point = points[j];
            QVector4D tempPoint(point);
            Matrix tempMatrix(tempPoint);

            Matrix rotateX = cam.getMatrixRotateY(angle);

            Matrix result = multiplicationMatrix(tempMatrix, rotateX);

            int x = result.getElement(0, 0);
            int y = result.getElement(0, 1);
            int z = result.getElement(0, 2);

            if (j == 0)
                faces[i].setA(QVector3D(x,y,z));

            if (j == 1)
                faces[i].setB(QVector3D(x,y,z));

            if (j == 2)
                faces[i].setC(QVector3D(x,y,z));
        }
    }
}


void Scene::rotateZ(double angle)
{
    for (size_t i = 0; i < faces.size(); i++)
    {
        auto points = faces[i].getPoints();

        for (size_t j = 0; j < 3; j++)
        {
            QVector3D point = points[j];
            QVector4D tempPoint(point);
            Matrix tempMatrix(tempPoint);

            Matrix rotateX = cam.getMatrixRotateZ(angle);

            Matrix result = multiplicationMatrix(tempMatrix, rotateX);

            int x = result.getElement(0, 0);
            int y = result.getElement(0, 1);
            int z = result.getElement(0, 2);

            if (j == 0)
                faces[i].setA(QVector3D(x,y,z));

            if (j == 1)
                faces[i].setB(QVector3D(x,y,z));

            if (j == 2)
                faces[i].setC(QVector3D(x,y,z));
        }
    }
}

