#ifndef CUBE_H
#define CUBE_H

#include <QDebug>
#include "point.h"
#include "pixel.h"
#include "matrix.h"

#define A 0
#define B 1
#define C 2
#define D 3
#define E 4
#define F 5
#define G 6
#define H 7

class Cube
{
private:
    Point3D *P, spectator;
    Point *castedPoints;
    Point3D *center = new Point3D;
    Point3D *current_center = new Point3D;
    Matrix matrix = {4};
    int offset, size;
    bool corners = false;
    void debugPoints(Point3D *P);
    void debugCastedPoints();
public:
    Cube();
    Cube(Point3D center, int size, int offset);
    ~Cube();
    void setup(Point3D center, int size, int offset);
    void draw(QImage *img);
    void drawPoints(QImage *img, Point *points);
    void drawLines(QImage *img, Point *points);
    void setFov(int value);
    void translate(Point3D *point);
    void scale(double sX, double sY, double sZ);
    void rotateX(double angle, int width, int height);
    void rotateY(double angle, int width, int height);
    void rotateZ(double angle);
    void genericDebug(QImage *img);
    Point *cast(Point3D *input);
    void setCornersVisible();
};

#endif // CUBE_H
