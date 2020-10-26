#include "cube.h"

Cube::Cube(Point3D center, int size, int offset) {
    P = new Point3D[8];
    castedPoints = new Point[8];
    this->setup(center, size, offset);
}
Cube::Cube(){
    P = new Point3D[8];
}
Cube::~Cube(){
    delete P;
    delete castedPoints;
    delete center;
    delete current_center;
}
void Cube::setup(Point3D center, int size, int offset)
{
    this->center->x = center.x;
    this->center->y = center.y;
    this->center->z = center.z;
    center.x = 0;
    center.y = 0;
    center.z = 0;
    P[_A_].x = center.x - size;
    P[_A_].y = center.y - size;
    P[_A_].z = center.z - size;

    P[_B_].x = center.x + size;
    P[_B_].y = center.y - size;
    P[_B_].z = center.z - size;

    P[_C_].x = center.x - size;
    P[_C_].y = center.y + size;
    P[_C_].z = center.z - size;

    P[_D_].x = center.x + size;
    P[_D_].y = center.y + size;
    P[_D_].z = center.z - size;

    P[_E_].x = center.x - size;
    P[_E_].y = center.y - size;
    P[_E_].z = center.z + size;

    P[_F_].x = center.x + size;
    P[_F_].y = center.y - size;
    P[_F_].z = center.z + size;

    P[_G_].x = center.x - size;
    P[_G_].y = center.y + size;
    P[_G_].z = center.z + size;

    P[_H_].x = center.x + size;
    P[_H_].y = center.y + size;
    P[_H_].z = center.z + size;

    spectator.x = center.x;
    spectator.y = center.y;
    spectator.z = -(offset);
    this->offset = offset;

}
void Cube::draw(QImage *img) {
    Pixel::clear(img);
    current_center = matrix.multiply3D(center);
    matrix.combine();
    Point3D *transformatedPoints = matrix.multiply3D(P);
    if(wireframe) {
        Point *points = cast(transformatedPoints, 8);
        drawLines(img, points);
        if(corners)
            drawPoints(img, points);
        delete transformatedPoints;
    } else {
        updateSurfaces(transformatedPoints);
        for(int i = 0; i < 6; i++) {
            if(isVisible(&surface[i]))
                drawSurface(img, &surface[i]);
        }
    }
}
bool Cube::isVisible(Rect *rect) {
    Point3D v, w, normal;
    v.x = rect->D.x - rect->C.x;
    v.y = rect->D.y - rect->C.y;
    v.z = rect->D.z - rect->C.z;

    w.x = rect->A.x - rect->C.x;
    w.y = rect->A.y - rect->C.y;
    w.z = rect->A.z - rect->C.z;

    normal = crossProduct(v, w);
    spectator.x = rect->C.x;
    spectator.y = rect->C.y;
    spectator.z = rect->C.z + offset;
    double dot_product = dotProduct(normal, spectator);
    return flip_normals ? dot_product > 0 : dot_product < 0;
}
double Cube::dotProduct(Point3D normal, Point3D spectator) {
    return normal.x * spectator.x + normal.y * spectator.y + normal.z * spectator.z;
}
Point3D Cube::crossProduct(Point3D v, Point3D w) {
    Point3D normal;
    normal.x = v.y * w.z - w.y * v.z;
    normal.y = w.x * v.z - v.x * w.z;
    normal.z = v.x * w.y - w.x * v.y;
    return normal;
}
void Cube::drawSurface(QImage *img, Rect *rect) {
    Point *output;
    Point3D *input = new Point3D[4];
    Color *color = new Color(0, 255, 0);
    input[_A_] = rect->A;
    input[_B_] = rect->B;
    input[_C_] = rect->C;
    input[_D_] = rect->D;
    output = cast(input, 4);
    for(int i = 0; i < 3; i++)
        Geometry::line(img, &output[i], &output[i + 1], color);
    Geometry::line(img, &output[3], &output[0], color);
    delete  color;
}
Point *Cube::cast(Point3D *input, int count) {
    Point *output = new Point[count];
    for(int i = 0; i < count; i++) {
        output[i].x = (input[i].x * offset) / (input[i].z + offset) + center->x;
        output[i].y = (input[i].y * offset) / (input[i].z + offset) + center->y;
    }
    return output;
}
void Cube::updateSurfaces(Point3D *P) {
    // L shape for proper vector calc
    surface[FRONT].A = P[_A_];
    surface[FRONT].B = P[_C_];
    surface[FRONT].C = P[_D_];
    surface[FRONT].D = P[_B_];
    surface[TOP].A = P[_E_];
    surface[TOP].B = P[_A_];
    surface[TOP].C = P[_B_];
    surface[TOP].D = P[_F_];
    surface[BOTTOM].A = P[_C_];
    surface[BOTTOM].B = P[_G_];
    surface[BOTTOM].C = P[_H_];
    surface[BOTTOM].D = P[_D_];
    surface[LEFT].A = P[_E_];
    surface[LEFT].B = P[_G_];
    surface[LEFT].C = P[_C_];
    surface[LEFT].D = P[_A_];
    surface[RIGHT].A = P[_B_];
    surface[RIGHT].B = P[_D_];
    surface[RIGHT].C = P[_H_];
    surface[RIGHT].D = P[_F_];
    surface[BACK].A = P[_G_];
    surface[BACK].B = P[_E_];
    surface[BACK].C = P[_F_];
    surface[BACK].D = P[_H_];
}
void Cube::drawPoints(QImage *img, Point *points) {
    Color *color = new Color(0, 255, 0);
    for(int i = 0; i < 8; i++)
        Pixel::drawPoint(img->bits(), &points[i], img->width(), color);
    delete color;
}
void Cube::drawLines(QImage *img, Point *points) {
    Color *color = new Color(0, 255, 0);

    Geometry::line(img, &points[0], &points[1], color);
    Geometry::line(img, &points[0], &points[2], color);
    Geometry::line(img, &points[0], &points[4], color);
    Geometry::line(img, &points[5], &points[4], color);
    Geometry::line(img, &points[5], &points[7], color);
    Geometry::line(img, &points[5], &points[1], color);
    Geometry::line(img, &points[6], &points[7], color);
    Geometry::line(img, &points[6], &points[4], color);
    Geometry::line(img, &points[6], &points[2], color);
    Geometry::line(img, &points[3], &points[7], color);
    Geometry::line(img, &points[3], &points[2], color);
    Geometry::line(img, &points[1], &points[3], color);
    delete color;
}
void Cube::setFov(int value) {
    this->spectator.z = -value;
    offset = value;
    qDebug() << "Fov: " << spectator.z;

}
void Cube::translate(Point3D *point) {
    matrix.translate3D(point);
}
void Cube::scale(double sX, double sY, double sZ) {
    matrix.scale3D(sX, sY, sZ);
}
void Cube::rotateZ(double angle) {
    int *center = new int[3];
    center[X] = 0;
    center[Y] = 0;
    center[Z] = 0;
    matrix.rotateZ(angle, center);
    delete[] center;
}
void Cube::rotateY(double angle) {
    int *center = new int[3];
    center[X] = 0;
    center[Y] = 0;
    center[Z] = 0;
    matrix.rotateY(angle, center);
    delete[] center;
}
void Cube::rotateX(double angle) {
    int *center = new int[3];
    center[X] = 0;
    center[Y] = 0;
    center[Z] = 0;
    matrix.rotateX(angle, center);
    delete[] center;
}
void Cube::genericDebug(QImage *img) {
    Point *point = new Point;
    Color *color = new Color(255, 255, 255);
    Pixel::drawPoint(img->bits(), point, img->width(), color);
    delete point;
    delete color;
}
void Cube::setCornersVisible() {
    this->corners = !this->corners;
}
void Cube::reset() {
    matrix.reset();
}
void Cube::toggleWireframe() {
    this->wireframe = !this->wireframe;
}
void Cube::toggleNormals() {
    this->flip_normals = !this->flip_normals;
}
void Cube::debugCastedPoints() {
    qDebug() << "A(" << castedPoints[_A_].x << castedPoints[_A_].y << ")";
    qDebug() << "B(" << castedPoints[_B_].x << castedPoints[_B_].y << ")";
    qDebug() << "C(" << castedPoints[_C_].x << castedPoints[_C_].y << ")";
    qDebug() << "D(" << castedPoints[_D_].x << castedPoints[_D_].y << ")";
    qDebug() << "E(" << castedPoints[_E_].x << castedPoints[_E_].y << ")";
    qDebug() << "F(" << castedPoints[_F_].x << castedPoints[_F_].y << ")";
    qDebug() << "G(" << castedPoints[_G_].x << castedPoints[_G_].y << ")";
    qDebug() << "H(" << castedPoints[_H_].x << castedPoints[_H_].y << ")";
}
void Cube::debugPoints(Point3D *P) {
    qDebug() << "A(" << P[_A_].x << P[_A_].y << P[_A_].z << ")";
    qDebug() << "B(" << P[_B_].x << P[_B_].y << P[_B_].z << ")";
    qDebug() << "C(" << P[_C_].x << P[_C_].y << P[_C_].z << ")";
    qDebug() << "D(" << P[_D_].x << P[_D_].y << P[_D_].z << ")";
    qDebug() << "E(" << P[_E_].x << P[_E_].y << P[_E_].z << ")";
    qDebug() << "F(" << P[_F_].x << P[_F_].y << P[_F_].z << ")";
    qDebug() << "G(" << P[_G_].x << P[_G_].y << P[_G_].z << ")";
    qDebug() << "H(" << P[_H_].x << P[_H_].y << P[_H_].z << ")";
}
