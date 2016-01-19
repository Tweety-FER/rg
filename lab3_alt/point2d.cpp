#include "point2d.h"
using namespace std;

Point2D::Point2D(float a, float b) {
    x = a;
    y = b;
}
    
void Point2D::move(Point2D offset) {
    x += offset.x;
    y += offset.y;
}
