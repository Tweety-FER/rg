#ifndef POINT2D_H
#define POINT2D_H
using namespace std;

struct Point2D {
    float x;
    float y;

    Point2D(float a, float b);
    
    void move(Point2D offset);
};

#endif
