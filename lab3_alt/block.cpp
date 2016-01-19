#include "block.h"
#include <iostream>
#define in_range(v, x, dx) ((dx) < 0 ? in_range2((v), (x) + (dx), -(dx)) : in_range2(v, x, dx))
#define in_range2(v, x, dx) ((v) >= (x) && (v) <= ((x) + (dx)))

using namespace std;

Block::Block(Point2D s, double w, double h) :
    Rectangle(s,w,h), hit(1) {};

void Block::draw() {
    if(hit > 0) {
        Rectangle::draw();
    }
}

bool Block::collideWithBall(Ball* b) {
    if(hit <= 0) return false;

    bool hitOne = false;

    double bx = b->getPosition().x
         , by = b->getPosition().y
         , br = b->getRadius()
         , x0 = getPosition().x
         , x1 = x0 + getWidth()
         , y0 = getPosition().y
         , y1 = y0 + getHeight();

    Point2D bv = b->getVelocity();

    //Bottom collision
    bool touchingBottom = by - br <= y0 && by + br >= y0;
    bool touchingTop = by - br <= y1 && by + br >= y1;
    bool touching = touchingTop || touchingBottom;

    if(bx - br >= x0 && bx + br <= x1 && touching) {
       b->setVelocity(Point2D(bv.x, - bv.y));
       this->hit--;
       hitOne = true;
    }

    //In case we are doing two updates
    bv = b->getVelocity();

    bool touchingLeft = bx - br <= x0 && bx + br >= x0;
    bool touchingRight = bx - br <= x1 && bx + br >= x1;
    touching = touchingLeft || touchingRight;
    //Left or right collision
    if(by - br >= y0 && by + br <= y1 && touching) {
        b->setVelocity(Point2D(-bv.x, bv.y));
        this->hit--;
        hitOne = true;
    }
    
    return hitOne;
}
