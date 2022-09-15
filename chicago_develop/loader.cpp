#include "loader.h"

Loader::Loader()
{
    file = std::make_shared<std::ifstream>();
}


int Loader::checkFile(std::string &filename)
{
    file->open(filename);

    if (!file)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}


std::vector<Triangle> Loader::readFaces()
{
    std::vector<Triangle> faces;

    std::string string;

    std::string num0;
    std::string num1;
    std::string num2;

    while(!file->eof())
    {
        *file >> string;

        if (string == "o")
        {
            std::vector<Triangle> currentFaces;
            std::vector<QVector3D> points;

            *file >> string; // name
            *file >> string;

            while (string == "v")
            {
                *file >> num0;
                *file >> num1;
                *file >> num2;

                QVector3D point(stoi(num0), stoi(num1), stoi(num2));
                points.push_back(point);

                *file >> string;
            }

            while (string == "f")
            {
               *file >> num0;
               *file >> num1;
               *file >> num2;

               Triangle face(points.at(stoi(num0) - 1), points.at(stoi(num1) - 1),
                             points.at(stoi(num2) - 1), QColor(50, 50, 50));
               currentFaces.push_back(face);

               *file >> string;
            }

            if (string == "Ka")
            {

                *file >> num0;
                *file >> num1;
                *file >> num2;

                for (size_t i = 0; i < currentFaces.size(); i++)
                {
                    currentFaces[i].setColor(QColor(stoi(num0), stoi(num1), stoi(num2)));
                    faces.push_back(currentFaces[i]);
                }
            }
         }
    }

    return faces;
}
