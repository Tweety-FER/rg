#include "point.h"
#include "rectangle.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

Rectangle::Rectangle(Point2D s0, Point2D dims) :
    Rectangle(s0, dims.x, dims.y) {}

Rectangle::Rectangle(Point2D s0, double w, double h) :
    Drawable(Point(0.0f, 0.0f, 1.0f)),
    position (s0),
    width (w),
    height (h) {}

Point2D Rectangle::getPosition() {
    return this->position;
}

void Rectangle::setPosition(Point2D s0) {
    this->position = s0;
}

double Rectangle::getWidth() {
    return this->width;
}

void Rectangle::setWidth(double w) {
    this->width = w;
}

double Rectangle::getHeight() {
    return this->height;
}

void Rectangle::setHeight(double h) {
    this->height = h;
}

Point2D Rectangle::getDimensions() {
    return Point2D(width, height);
}

void Rectangle::setDimensions(Point2D p) {
    width = p.x;
    height = p.y;
}

void Rectangle::move(Point2D offset) {
    position.move(offset);
}

void Rectangle::draw() {
    glColor3f(colour.x, colour.y, colour.z);

    glBegin(GL_QUADS);
        glVertex2f(position.x, position.y);
        glVertex2f(position.x + width, position.y);
        glVertex2f(position.x + width, position.y + height);
        glVertex2f(position.x, position.y + height);
    glEnd();
}
