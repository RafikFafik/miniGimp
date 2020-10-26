#ifndef CUBE_H
#define CUBE_H

#include <QDebug>
#include "point.h"
#include "pixel.h"
#include "matrix.h"

#define _A_ 0
#define _B_ 1
#define _C_ 2
#define _D_ 3
#define _E_ 4
#define _F_ 5
#define _G_ 6
#define _H_ 7
#define FRONT 0
#define TOP 1
#define BOTTOM 2
#define LEFT 3
#define RIGHT 4
#define BACK 5

class Cube
{
private:
    Point3D *P, spectator;
    Point *castedPoints;
    Point3D *center = new Point3D;
    Point3D *current_center = new Point3D;
    Rect surface[6];
    Matrix matrix = {4};
    int offset, size;
    bool corners = false;
    bool wireframe = false;
    bool flip_normals = false;
    void debugPoints(Point3D *P);
    void debugCastedPoints();
    void updateSurfaces(Point3D *P);
    bool isVisible(Rect *rect);
    void drawSurface(QImage *img, Rect *rect);
    Point3D crossProduct(Point3D v, Point3D w);
    double dotProduct(Point3D xWw, Point3D spectator);
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
    void rotateX(double angle);
    void rotateY(double angle);
    void rotateZ(double angle);
    void genericDebug(QImage *img);
    Point *cast(Point3D *input, int count);
    void setCornersVisible();
    void reset();
    void toggleWireframe();
    void toggleNormals();
};

#endif // CUBE_H
