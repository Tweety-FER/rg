#ifndef PADDLE_H
#define PADDLE_H

#include "rectangle.h"
#include "point2d.h"

class Paddle : public Rectangle {
    private:
        double velocity;

    public:
        Paddle(Point2D s0, double w, double h, double v);

        void moveLeft();

        void moveRight();
};

#endif
