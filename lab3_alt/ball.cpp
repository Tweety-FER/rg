#include "point.h"
#include "ball.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

Ball::Ball(Point2D s, Point2D v, double r) :
    Drawable(Point(1.0f, 1.0f, 1.0f)),
    position (s),
    velocity (v),
    radius (r) {};

Point2D Ball::getPosition() {
    return this->position;
}

void Ball::setPosition(Point2D s) {
    this->position = s;
}

Point2D Ball::getVelocity() {
    return this->velocity;
}

void Ball::setVelocity(Point2D v) {
    this->velocity = v;
}

double Ball::getRadius() {
    return this->radius;
}

void Ball::setRadius(double r) {
    this->radius = r;
}

void Ball::move() {
    position.move(velocity);
}

void Ball::draw() {
    glPointSize((float) 2.0 * radius);
    glColor3f(colour.x, colour.y, colour.y);
    glBegin(GL_POINTS);
    glVertex2f(position.x, position.y);
    glEnd();
}
