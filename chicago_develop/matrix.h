#ifndef MATRIX_H
#define MATRIX_H


#include <memory>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <QVector4D>

class Matrix
{
    public:
        Matrix();
        Matrix(int specificRow, int specificColumn);
        Matrix(int specificRow, int specificColumn, double **specificMatrix);
        Matrix(QVector4D vector);

        double **getMatrix(){return matrix;};
        int getRow(){return row;};
        int getColumn(){return column;};

        void setELement(int rowIndex, int columnIndex, double num);
        double getElement(int rowIndex, int columnIndex){return matrix[rowIndex][columnIndex];};

        void printMatrix();

   private:
        int row;
        int column;

        double **matrix;

};

Matrix multiplicationMatrix(Matrix firstMatrix, Matrix secondMatrix);


#endif // MATRIX_H

