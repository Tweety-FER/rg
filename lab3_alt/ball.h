#ifndef BALL_H
#define BALL_H

#include "point2d.h"
#include "drawable.h"

using namespace std;

class Ball : Drawable {
    private:
        Point2D position;
        Point2D velocity;
        double  radius;
    public:
        Ball(Point2D s, Point2D v, double r);

        Point2D getPosition();

        void setPosition(Point2D s);

        Point2D getVelocity();

        void setVelocity(Point2D v);

        double getRadius();

        void setRadius(double r);

        virtual void draw();

        void move();
};

#endif
