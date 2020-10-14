#ifndef MATRIX_H
#define MATRIX_H
#include <QDebug>
#include "point.h"

class Matrix
{
private:
    double **transformationMatrix, **translationMatrix, **aux;
    double **scaleMatrix, **rotationMatrix, **sheareMatrix;
    void clearVector(double *vector);
    unsigned int size;
    void multiplyMatrix(double **factor);

    void sheare(double x, double y, int width, int height);
public:
    Matrix(unsigned int size);
    ~Matrix();
    void reset();
    double* multiply(double *input, double *output);
    void translate(Point *vector);
    void scale(double sX, double sY, int width, int height);
    void rotate(double angle, int width, int height);    
    void sheareX(double a, int distance);
    void sheareY(double a, int distance);
    void clear(double **matrix);
    void debug();
    void combine();
};

#endif // MATRIX_H
