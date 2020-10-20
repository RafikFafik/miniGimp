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
    P[A].x = center.x - size;
    P[A].y = center.y - size;
    P[A].z = center.z - size;

    P[B].x = center.x + size;
    P[B].y = center.y - size;
    P[B].z = center.z - size;

    P[C].x = center.x - size;
    P[C].y = center.y + size;
    P[C].z = center.z - size;

    P[D].x = center.x + size;
    P[D].y = center.y + size;
    P[D].z = center.z - size;

    P[E].x = center.x - size;
    P[E].y = center.y - size;
    P[E].z = center.z + size;

    P[F].x = center.x + size;
    P[F].y = center.y - size;
    P[F].z = center.z + size;

    P[G].x = center.x - size;
    P[G].y = center.y + size;
    P[G].z = center.z + size;

    P[H].x = center.x + size;
    P[H].y = center.y + size;
    P[H].z = center.z + size;

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

    debugPoints(transformatedPoints);
    Point *points = cast(transformatedPoints);
    delete transformatedPoints;
    if(corners)
        drawPoints(img, points);
    drawLines(img, points);


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
Point *Cube::cast(Point3D *input) {
    Point *xd = new Point[8];
    for(int i = 0; i < 8; i++) {
        xd[i].x = (input[i].x * offset) / (input[i].z + offset) + center->x;
        xd[i].y = (input[i].y * offset) / (input[i].z + offset) + center->y;
    }
    return xd;
}
void Cube::translate(Point3D *point) {
    matrix.translate3D(point);
}
void Cube::scale(double sX, double sY, double sZ) {
    matrix.scale3D(sX, sY, sZ);
}
void Cube::rotateZ(double angle) {
    int *center = new int[3];
//    center[X] = this->current_center->x *(1-cos(angle)) + this->current_center->y * sin(angle);
//    center[Y] = this->current_center->y *(1-cos(angle)) - this->current_center->x * sin(angle);
    center[X] = 0;
    center[Y] = 0;
    center[Z] = this->center->z;
    matrix.rotateZ(angle, center);
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
void Cube::debugCastedPoints() {
    qDebug() << "A(" << castedPoints[A].x << castedPoints[A].y << ")";
    qDebug() << "B(" << castedPoints[B].x << castedPoints[B].y << ")";
    qDebug() << "C(" << castedPoints[C].x << castedPoints[C].y << ")";
    qDebug() << "D(" << castedPoints[D].x << castedPoints[D].y << ")";
    qDebug() << "E(" << castedPoints[E].x << castedPoints[E].y << ")";
    qDebug() << "F(" << castedPoints[F].x << castedPoints[F].y << ")";
    qDebug() << "G(" << castedPoints[G].x << castedPoints[G].y << ")";
    qDebug() << "H(" << castedPoints[H].x << castedPoints[H].y << ")";
}
void Cube::debugPoints(Point3D *P) {
    qDebug() << "A(" << P[A].x << P[A].y << P[A].z << ")";
    qDebug() << "B(" << P[B].x << P[B].y << P[B].z << ")";
    qDebug() << "C(" << P[C].x << P[C].y << P[C].z << ")";
    qDebug() << "D(" << P[D].x << P[D].y << P[D].z << ")";
    qDebug() << "E(" << P[E].x << P[E].y << P[E].z << ")";
    qDebug() << "F(" << P[F].x << P[F].y << P[F].z << ")";
    qDebug() << "G(" << P[G].x << P[G].y << P[G].z << ")";
    qDebug() << "H(" << P[H].x << P[H].y << P[H].z << ")";
}
