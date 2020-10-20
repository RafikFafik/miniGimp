#ifndef MATRIX_H
#define MATRIX_H
#include <QDebug>
#include "point.h"

#define X 0
#define Y 1
#define Z 2

class Matrix
{
private:
    double **transformationMatrix, **translationMatrix, **aux, **persp;
    double **scaleMatrix, **sheareMatrix, **rotationMatrixX, **rotationMatrixY, **rotationMatrixZ;
    void clearVector(double *vector);
    unsigned int size;
    void multiplyMatrix(double **factor);

    void sheare(double x, double y, int width, int height);
public:
    Matrix(unsigned int size);
    ~Matrix();
    void reset();
    double* multiply(double *input, double *output);
    Point3D *multiply3D(Point3D *P);
    void translate(Point *vector);
    void translate3D(Point3D *vector);
    void scale(double sX, double sY, int width, int height);
    void scale3D(double sX, double sY, double sZ);
    void rotateX(double angle);
    void rotateY(double angle);
    void rotateZ(double angle, int *center);
    void sheareX(double a, int distance);
    void sheareY(double a, int distance);
    void clear(double **matrix);
    void debug(double **matrix);
    void combine();
};

#endif // MATRIX_H
