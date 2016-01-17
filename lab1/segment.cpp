#pragma once
#include <math.h>
#include <vector>

struct Segment {
    Point a;
    Point b;
    Point c;
    Point d;

    Point& operator[] (int i) {
        switch((i + 4) % 4) {
            case 0 : return a;
            case 1 : return b;
            case 2 : return c;
            case 3 : return d;
            default: return a;
        };
    };
};

struct BSpline {
    Point point;
    Point tangent;
};

vector<Segment> readSegments(string file_path, bool scaled) {
    vector<Point> points = read_points(file_path, scaled);
    vector<Segment> segments;

    for(unsigned int i = 1; i < points.size() - 2; i++) {
        Segment s;
        s.a = points[i - 1];
        s.b = points[i];
        s.c = points[i + 1];
        s.d = points[i + 2];

        segments.push_back(s);
    }

    return segments;
}

Point curvePoint(double t, Segment s) {
    double C = 1.0 / 6.0;
    double ts[4] = { C * pow(t, 3), C * pow(t, 2), C * t, C };
    double B[4][4] = {{-1, 3, -3, 1}, {3, -6, 3, 0}, {-3, 0, 3, 0}, {1, 4, 1, 0}};

    int i, j;

    double tmp[4] = {0};

    //Temp result
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            tmp[i] += ts[j] * B[j][i];
        }
    }

    Point p;

    for(i = 0; i < 3; i++) {
        p[i] = 0;

        for(j = 0; j < 4; j++) {
            p[i] += tmp[j] * s[j][i];     
        }
    }

    return p;
}

Point tangent(double t, Segment s) {
    double C = 0.5;
    double ts[4] = {C * pow(t, 2), C * t, C};
    double B[3][4] = {{-1, 3, -3, 1},{2, -4, 2, 0}, {-1, 0, 1, 0}};

    int i, j;

    double tmp[4] = {0};

    for(i = 0; i < 4; i++) {
        for(j = 0; j < 3; j++) {
            tmp[i] += ts[j] * B[j][i];
        }
    }

    Point p;

    for(i = 0; i < 3; i++) {
        p[i] = 0;

        for(j = 0; j < 4; j++) {
            p[i] += tmp[j] * s[j][i];
        }
    }

    return p;
}

vector<BSpline> readMoves(string file_path, double t_step, bool scaled) {
    vector<Segment> segments = readSegments(file_path, scaled);
    vector<BSpline> splines;
    
    unsigned int i;
    double t;

    for(i = 0; i < segments.size(); i++) {
        for(t = 0.0; t < 1.0; t += t_step) {
            BSpline b;
            b.point = curvePoint(t, segments[i]);
            b.tangent = tangent(t, segments[i]);

            splines.push_back(b);
        }
    }

    return splines;
};
