#include "matrix.h"
#include <cmath>
Matrix::Matrix(unsigned int incomingSize) : size(incomingSize)
{
    transformationMatrix = new double*[size];
    translationMatrix = new double*[size];
    scaleMatrix = new double*[size];
    rotationMatrix = new double*[size];
    sheareMatrix = new double*[size];
    aux = new double*[size];
    for(unsigned int i = 0; i < size; i++) {
        transformationMatrix[i] = new double[size];
        translationMatrix[i] = new double[size];
        scaleMatrix[i] = new double[size];
        rotationMatrix[i] = new double[size];
        sheareMatrix[i] = new double[size];
        aux[i] = new double[size];
    }
    for(unsigned int i = 0; i < size; i++) {
        for(unsigned int j = 0; j < size; j++)
            i == j ? transformationMatrix[i][j] = translationMatrix[i][j] = aux[i][j] = scaleMatrix[i][j] = rotationMatrix[i][j] = sheareMatrix[i][j] =  1 :
                    transformationMatrix[i][j] =  translationMatrix[i][j] = aux[i][j] = scaleMatrix[i][j] = rotationMatrix[i][j] = sheareMatrix[i][j] = 0;
    }
//    debug();
}
Matrix::~Matrix() {
    for(unsigned int i = 0; i < size; i++) {
        delete translationMatrix[i];
        delete transformationMatrix[i];
        delete scaleMatrix[i];
        delete rotationMatrix[i];
        delete sheareMatrix[i];
    }

    delete translationMatrix;
    delete transformationMatrix;
    delete scaleMatrix;
    delete rotationMatrix;
    delete sheareMatrix;
}
void Matrix::translate(Point *vector) {
    translationMatrix[0][size - 1] = vector->x;
    translationMatrix[1][size - 1] = vector->y;
}
void Matrix::scale(double sX, double sY, int width, int height) {
    scaleMatrix[0][0] = sX;
    scaleMatrix[1][1] = sY;
    scaleMatrix[0][2] = (1 - sX) *  width / (double)2;
    scaleMatrix[1][2] = (1 - sY) * height / (double)2;
}
void Matrix::rotate(double angle, int width, int height) {
    rotationMatrix[0][0] = cos(angle);
    rotationMatrix[0][1] = -sin(angle);
    rotationMatrix[0][2] = (width / (double)2)*(1-cos(angle))+(height/(double)2)*(sin(angle));
    rotationMatrix[1][0] = sin(angle);
    rotationMatrix[1][1] = cos(angle);
    rotationMatrix[1][2] = (height/(double)2)*(1-cos(angle))-(width/(double)2)*(sin(angle));
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
    clear(rotationMatrix);
    clear(sheareMatrix);
}
void Matrix::clear(double **matrix) {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++)
            i == j ? matrix[i][j] = 1 : matrix[i][j] = 0;
    }
}
void Matrix::combine() {
    clear(transformationMatrix);
    multiplyMatrix(rotationMatrix);
    multiplyMatrix(scaleMatrix);
    multiplyMatrix(sheareMatrix);
    multiplyMatrix(translationMatrix);
//    debug();
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
void Matrix::multiplyMatrix(double **factor) {
    int i,j,k;
        double s;
        for(i = 0; i < 3; i++) {
            for(j = 0; j < 3; j++) {
                s = 0;
                for(k = 0; k < 3; k++) {
                    s += transformationMatrix[i][k] * factor[k][j];
                }
                aux[i][j] = s;
            }
        }
        for(i = 0; i < 3; i++){
            for(j = 0; j < 3; j++){
                transformationMatrix[i][j] = aux[i][j];
            }
        }
}

void Matrix::debug() {
    qDebug() << "Transformation matrix:";
    for(unsigned int i = 0; i < size; i++) {
        for(unsigned int j = 0; j < size; j++) {
            qDebug() << transformationMatrix[i][j] << " ";
        }
        qDebug() << "";
   }

}
void Matrix::clearVector(double *vector) {
    for(unsigned int i = 0; i < size; i++) {
        vector[i] = 0;
    }
}
