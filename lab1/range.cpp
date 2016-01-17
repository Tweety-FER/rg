#pragma once
#include "point.cpp"
#include <cstdlib>

using namespace std;

class Range
{
    double min;
    double max;

    public:
        Range() {};
        Range(double min, double max) {
            this->min = min;
            this->max = max;
        }

        double yield() {
            double f = (double) rand() / RAND_MAX;
            return min + f * (max - min);
        }
};

class PointRange
{
    Range rx;
    Range ry;
    Range rz;

    public:
        PointRange() {};
        PointRange(Range x, Range y, Range z) : rx(x), ry(y), rz(z) {};
        Point yield() {
            return Point(rx.yield(), ry.yield(), rz.yield());
        }
};

