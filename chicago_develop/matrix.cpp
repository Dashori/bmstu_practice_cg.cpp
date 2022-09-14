#include "matrix.h"

Matrix::Matrix()
{

}

Matrix::Matrix(int specificRow, int specificColumn)
    :row(specificRow),
     column(specificColumn)
{
    matrix = new double *[row];

    for (int i = 0; i < row; i++)
    {
        matrix[i] = new double[column];

        for (int j = 0; j < column; j++)
            matrix[i][j] = 0;
    }
}

Matrix::Matrix(QVector4D vector)
    : row(1),
      column(4)

{
    matrix = new double *[row];

    for (int i = 0; i < row; i++)
        matrix[i] = new double[column];


    matrix[0][0] = vector.x();
    matrix[0][1] = vector.y();
    matrix[0][2] = vector.z();
    matrix[0][3] = vector.w();
}


Matrix::Matrix(int specificRow, int specificColumn, double **specificMatrix)
    :row(specificRow),
     column(specificColumn)
{
    matrix = new double *[row];

    for (int i = 0; i < row; i++)
    {
        matrix[i] = new double[column];

        for (int j = 0; j < column; j++)
            matrix[i][j] = specificMatrix[i][j];
    }
}


void Matrix::setELement(int rowIndex, int columnIndex, double num)
{
    matrix[rowIndex][columnIndex] = num;
}


Matrix multiplicationMatrix(Matrix firstMatrix, Matrix secondMatrix)
{
    auto firstRow = firstMatrix.getRow();
    auto firstColumn = firstMatrix.getColumn();
    auto firstData = firstMatrix.getMatrix();

    auto secondRow = secondMatrix.getRow();
    auto secondColumn = secondMatrix.getColumn();
    auto secondData = secondMatrix.getMatrix();

    Matrix resultMatrix(firstColumn, secondRow);

    for (int i = 0; i < firstRow; i++)
    {
        for (int j = 0; j < secondColumn; j++)
        {
            double sum = 0;

            for (int k = 0; k < secondRow; k++)
                sum += firstData[i][k] * secondData[k][j];

            resultMatrix.setELement(i, j, sum);
        }
    }

    return resultMatrix;
}


void Matrix::printMatrix()
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
            std::cout << matrix[i][j] << " ";

        std::cout << " \n";
    }

    std::cout << "\n";
}
