#ifndef POINT_H
#define POINT_H

struct Point{
    int x, y;
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
    Point(){}
    bool operator== (const Point &a) {
        return (this->x == a.x && this->y == a.y);
    }
    bool operator!= (const Point &a) {
        return (this->x != a.x || this->y != a.y);
    }
    void operator* (const double &a) {
            this->x *= a;
            this->y *= a;
    }
    void operator+ (const double &a) {
            this->x += a;
            this->y += a;
    }
};
struct Point3D {
    int x, y, z;
};
struct Rect {
    Point3D A, B, C, D;
};

#endif // POINT_H
