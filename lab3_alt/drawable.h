#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "point.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

using namespace std;

class Drawable {
    protected:
        Point colour;

    public:
        Drawable(Point c);

        Point getColour();

        void setColour(Point c);

        virtual void draw() = 0;
};

#endif
