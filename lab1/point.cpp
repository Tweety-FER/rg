#pragma once
#include <fstream>
#include <GL/gl.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Point {
    public:
        double x;
        double y;
        double z;

        Point () {};

        Point (double a, double b, double c) : x(a), y(b), z(c) {};

        void parse(stringstream& s);

        double norm();

        Point unit();

        double dot(Point& p);

        Point cross(Point& p);

        double angle(Point& p);

        double& operator[] (int i) {
            switch((i + 3) % 3) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
                default : return x;
            }
        };

        Point operator+ (Point& p) {
            return Point(x + p.x, y + p.y, z + p.z);
        }

        Point operator- (Point& p) {
            return Point(x - p.x, y - p.y, z - p.z);
        }

        Point operator* (double s) {
            return Point(x * s, y * s, z * s);
        }

        void print() {
            cout << "(" << x << ", " << y << ", " << z << ")" << endl;
        }
};

double Point::norm() {
    return sqrt(x * x + y * y + z * z);
}

Point Point::unit() {
    double n = norm();
    Point p (x/n, y/n, z/n);

    return p;
}

void Point::parse(stringstream& ss) {
    ss >> x >> y >> z;
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

vector<Point> scale(vector<Point> points) {
    if(points.size() == 0) return points;

    double min_x = points[0].x
         , min_y = points[0].y
         , min_z = points[0].z
         , max_x = points[0].x
         , max_y = points[0].y
         , max_z = points[0].z;

    for(Point p : points) {
        if(p.x < min_x) min_x = p.x;
        if(p.x > max_x) max_x = p.x;
        if(p.y < min_y) min_y = p.y;
        if(p.y > max_y) max_y = p.y;
        if(p.z < min_z) min_z = p.z;
        if(p.z > max_z) max_z = p.z;
    }

    vector<Point> scaled;

    for(Point p : points) {
        Point s ( (p.x - min_x) / (max_x - min_x)
                , (p.y - min_y) / (max_y - min_y)
                , (p.z - min_z) / (max_z - min_z)
                );

        scaled.push_back(s);
    }

    return scaled;
}

vector<Point> read_points(string file_name, bool scaled) {
    fstream f;
    string line;
    vector<Point> points;

    f.open(file_name, ios::in);

    while(getline(f, line)) {
        //Skip empty or comments
        if(line.length() == 0 || line[0] == '#') continue;

        Point p;
        stringstream ss (line);
        p.parse(ss);

        points.push_back(p);
    }

    f.close();

    return scaled ? scale(points) : points;
}
