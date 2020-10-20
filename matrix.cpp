#include "matrix.h"
#include <cmath>
Matrix::Matrix(unsigned int incomingSize) : size(incomingSize)
{
    transformationMatrix = new double*[size];
    translationMatrix = new double*[size];
    scaleMatrix = new double*[size];
    rotationMatrixX = new double*[size];
    rotationMatrixY = new double*[size];
    rotationMatrixZ = new double*[size];
    sheareMatrix = new double*[size];
    aux = new double*[size];
    for(unsigned int i = 0; i < size; i++) {
        transformationMatrix[i] = new double[size];
        translationMatrix[i] = new double[size];
        scaleMatrix[i] = new double[size];
        rotationMatrixX[i] = new double[size];
        rotationMatrixY[i] = new double[size];
        rotationMatrixZ[i] = new double[size];
        sheareMatrix[i] = new double[size];
        aux[i] = new double[size];
    }
    for(unsigned int i = 0; i < size; i++) {
        for(unsigned int j = 0; j < size; j++) {
            if(i == j) {
                transformationMatrix[i][j] = 1;
                translationMatrix[i][j] =  1;
                aux[i][j] = 1;
                scaleMatrix[i][j] = 1;
                sheareMatrix[i][j] = 1;
                rotationMatrixX[i][j] = 1;
                rotationMatrixY[i][j] = 1;
                rotationMatrixZ[i][j] = 1;
            } else {
                transformationMatrix[i][j] = 0;
                translationMatrix[i][j] = 0;
                aux[i][j] = 0;
                scaleMatrix[i][j] = 0;
                sheareMatrix[i][j] = 0;
                rotationMatrixX[i][j] = 0;
                rotationMatrixY[i][j] = 0;
                rotationMatrixZ[i][j] = 0;
            }
        }

    }
//    debug();
}
Matrix::~Matrix() {
    for(unsigned int i = 0; i < size; i++) {
        delete translationMatrix[i];
        delete transformationMatrix[i];
        delete scaleMatrix[i];
        delete sheareMatrix[i];
        delete rotationMatrixX[i];
        delete rotationMatrixY[i];
        delete rotationMatrixZ[i];
    }

    delete translationMatrix;
    delete transformationMatrix;
    delete scaleMatrix;
    delete sheareMatrix;
    delete rotationMatrixX;
    delete rotationMatrixY;
    delete rotationMatrixZ;
}
void Matrix::translate(Point *vector) {
    translationMatrix[0][size - 1] = vector->x;
    translationMatrix[1][size - 1] = vector->y;
}
void Matrix::translate3D(Point3D *vector) {
    translationMatrix[0][size - 1] = -(vector->x);
    translationMatrix[1][size - 1] = vector->y;
    translationMatrix[2][size - 1] = vector->z;
}
void Matrix::scale(double sX, double sY, int width, int height) {
    scaleMatrix[0][0] = sX;
    scaleMatrix[1][1] = sY;
    scaleMatrix[0][2] = (1 - sX) *  width / (double)2;
    scaleMatrix[1][2] = (1 - sY) * height / (double)2;
}
void Matrix::scale3D(double sX, double sY, double sZ) {
    scaleMatrix[0][0] = sX;
    scaleMatrix[1][1] = sY;
    scaleMatrix[2][2] = sZ;
}
void Matrix::rotateZ(double angle, int *center) {
    rotationMatrixZ[0][0] = cos(angle);
    rotationMatrixZ[0][1] = -sin(angle);
    rotationMatrixZ[0][size - 1] = center[X];
    rotationMatrixZ[1][0] = sin(angle);
    rotationMatrixZ[1][1] = cos(angle);
    rotationMatrixZ[1][size - 1] = center[Y];
    rotationMatrixZ[2][size - 1] = center[Z];
}
void Matrix::rotateX(double angle) {
    rotationMatrixX[1][1] = cos(angle);
    rotationMatrixX[1][2] = -sin(angle);
//    rotationMatrixX[0][size - 1] = (width / (double)2)*(1-cos(angle))+(height/(double)2)*(sin(angle));
    rotationMatrixX[2][1] = sin(angle);
    rotationMatrixX[2][2] = cos(angle);
//    rotationMatrixX[1][size - 1] = (height/(double)2)*(1-cos(angle))-(width/(double)2)*(sin(angle));
}
void Matrix::rotateY(double angle) {
    rotationMatrixY[0][0] = cos(angle);
    rotationMatrixY[2][0] = -sin(angle);
//    rotationMatrixY[0][size - 1] = (width / (double)2)*(1-cos(angle))+(height/(double)2)*(sin(angle));
    rotationMatrixY[0][2] = sin(angle);
    rotationMatrixY[2][2] = cos(angle);
//    rotationMatrixY[1][size - 1] = (height/(double)2)*(1-cos(angle))-(width/(double)2)*(sin(angle));
}
void Matrix::sheareX(double a,int distance) {
    sheareMatrix[0][1] = a;
    sheareMatrix[0][2] = ((1 - a) *  (distance / (double)2)) - distance / 2;
}
void Matrix::sheareY(double a, int distance) {
    sheareMatrix[1][0] = a;
    sheareMatrix[1][2] = ((1 - a) *  (distance / (double)2)) - distance / 2;
}
void Matrix::reset() {
    clear(transformationMatrix);
    clear(translationMatrix);
    clear(scaleMatrix);
    clear(rotationMatrixZ);
    clear(rotationMatrixY);
    clear(rotationMatrixX);
    clear(sheareMatrix);
}
void Matrix::clear(double **matrix) {
    for(unsigned int i = 0; i < size; i++) {
        for(unsigned int j = 0; j < size; j++)
            i == j ? matrix[i][j] = 1 : matrix[i][j] = 0;
    }
}
void Matrix::combine() {
    clear(transformationMatrix);
    multiplyMatrix(rotationMatrixZ);
    multiplyMatrix(scaleMatrix);
    multiplyMatrix(sheareMatrix);
    multiplyMatrix(translationMatrix);
//    debug(transformationMatrix);
//    debug(translationMatrix);
}

double* Matrix::multiply(double *input, double *output) {
    for(unsigned int i = 0; i < size; i++)
        output[i] = 0;
    for(unsigned int i = 0; i < size; i++) {
        for(unsigned int j = 0; j < size; j++) {
            output[i] += transformationMatrix[i][j] * input[j];
        }
    }
    return output;
}
Point3D *Matrix::multiply3D(Point3D *P) {
    Point3D *result = new Point3D[8];
    for(int i = 0; i < 8; i++) {
        result[i].x = (P[i].x * transformationMatrix[0][0]) + (P[i].y * transformationMatrix[0][1]) + (P[i].z * transformationMatrix[0][2]) + transformationMatrix[0][3];
        result[i].y = (P[i].x * transformationMatrix[1][0]) + (P[i].y * transformationMatrix[1][1]) + (P[i].z * transformationMatrix[1][2]) + transformationMatrix[1][3];
        result[i].z = (P[i].x * transformationMatrix[2][0]) + (P[i].y * transformationMatrix[2][1]) + (P[i].z * transformationMatrix[2][2]) + transformationMatrix[2][3];
    }
    return result;
}
void Matrix::multiplyMatrix(double **factor) {
    double s;
    for(unsigned int i = 0; i < size; i++) {
        for(unsigned int j = 0; j < size; j++) {
            s = 0;
            for(unsigned int k = 0; k < size; k++) {
                s += transformationMatrix[i][k] * factor[k][j];
            }
            aux[i][j] = s;
        }
    }
    for(unsigned int i = 0; i < size; i++){
        for(unsigned int j = 0; j < size; j++){
            transformationMatrix[i][j] = aux[i][j];
        }
    }
}

void Matrix::debug(double **matrix) {
    qDebug() << "Matrix:";
    QDebug debug = qDebug();
    for(unsigned int i = 0; i < size; i++) {
        for(unsigned int j = 0; j < size; j++) {
           debug << matrix[i][j];
        }
        debug << "\n";
   }

}
void Matrix::clearVector(double *vector) {
    for(unsigned int i = 0; i < size; i++) {
        vector[i] = 0;
    }
}
