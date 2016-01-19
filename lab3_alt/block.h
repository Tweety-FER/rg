#ifndef BLOCK_H
#define BLOCK_H

#include "point2d.h"
#include "rectangle.h"
#include "ball.h"
#define TRUE 1
#define FALSE 0

class Block : public Rectangle {
    public:
        short hit;

        Block(Point2D s, double w, double h);

        void draw();

        bool collideWithBall(Ball* b);
};

#endif
