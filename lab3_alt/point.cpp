#include "point.h"
using namespace std;

Point::Point() : x(0.0), y(0.0), z(0.0) {};

Point::Point(double a, double b, double c) : x(a), y(b), z(c) {};

Point Point::operator+ (Point& p) {
    return Point(x + p.x, y + p.y, z + p.z);
}

Point Point::operator- (Point& p) {
    return Point(x - p.x, y - p.y, z - p.z);
}

Point Point::operator* (double s) {
    return Point(x * s, y * s, z * s);
}

double Point::norm() {
    return sqrt(x * x + y * y + z * z);
}

Point Point::unit() {
    double n = norm();
    Point p (x/n, y/n, z/n);

    return p;
}

double Point::dot(Point& p) {
    return x * p.x + y * p.y + z * p.z;
}

Point Point::cross(Point& p) {
    Point r;

    r.x = y * p.z - z * p.y;
    r.y = z * p.x - x * p.z;
    r.z = x * p.y - y * p.x;

    return r;
}

double Point::angle(Point& p) {
    double radians = acos(this->dot(p) / (norm() * p.norm()));

    return radians * 180.0 / M_PI;
}

