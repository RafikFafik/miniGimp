#ifndef POINT_H
#define POINT_H

class Point{

    public:
    int x, y;
public:
    Point();
    Point(int xpos, int ypos);
    int getX();
    int getY();
    void setX(int xpos);
    void setY(int ypos);
    void setPoint(int xpos, int ypos);
};

#endif // POINT_H
