#include "drawable.h"

using namespace std;

Drawable::Drawable(Point c) : colour(c) {};

Point Drawable::getColour() {
    return this->colour;
}

void Drawable::setColour(Point c) {
    this->colour = c;
}
