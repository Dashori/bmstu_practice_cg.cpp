#ifndef LOADER_H
#define LOADER_H

#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include <memory>
#include <string>

#include <QVector3D>
#include <QColor>

#include <fstream>

#include "triangle.h"

class Loader
{
    public:
        Loader();

        int checkFile(std::string &filename);

        std::vector<Triangle> readFaces();

        std::shared_ptr<std::ifstream> getFile(){return file;};

    private:
        std::shared_ptr<std::ifstream> file = nullptr;


};

#endif // LOADER_H
