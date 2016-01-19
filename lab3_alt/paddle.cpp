#include "paddle.h"
#include "point2d.h"

Paddle::Paddle(Point2D s0, double w, double h, double v) :
    Rectangle(s0, w, h),
    velocity(v) {};

void Paddle::moveLeft() {
    move(Point2D(-velocity, 0.0));
}

void Paddle::moveRight() {
    move(Point2D(velocity, 0.0));
}
