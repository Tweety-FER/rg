#ifndef POINT3D_H
#define POINT3D_H

#include <GL/gl.h>
#include <math.h>

using namespace std;

class Point {
    public:
        double x;
        double y;
        double z;

        Point();

        Point (double a, double b, double c);

        double norm();

        Point unit();

        double dot(Point& p);

        Point cross(Point& p);

        double angle(Point& p);

        Point operator+ (Point& p);

        Point operator- (Point& p);

        Point operator* (double s);
};


#endif
