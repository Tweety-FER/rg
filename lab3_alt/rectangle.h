#ifndef SQUARE_H
#define SQUARE_H

#include "point2d.h"
#include "drawable.h"

using namespace std;

class Rectangle : Drawable {
    private:
        Point2D position;
        double  width;
        double  height;

    public:
        Rectangle(Point2D s0, Point2D dims);

        Rectangle(Point2D s0, double w, double h);

        Point2D getPosition();

        void setPosition(Point2D s0);

        double getWidth();

        void setWidth(double w);

        double getHeight();

        void setHeight(double h);

        Point2D getDimensions();

        void setDimensions(Point2D dims);

        void move(Point2D offset);

        virtual void draw();
};

#endif
