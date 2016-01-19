#ifndef BLOCKS_H
#define BLOCKS_H

#include <vector>
#include "ball.h"
#include "block.h"
#include "point2d.h"

class Blocks {
    private:
        vector<vector<Block>> blocks;

    public:
        Blocks(Point2D topLeft, int rows, int cols, int block_w, int block_h, int gutter);

        void draw();

        void checkCollisions(Ball* b);
};

#endif
