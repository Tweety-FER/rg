#include "blocks.h"
#include <iostream>

using namespace std;

Blocks::Blocks(Point2D topLeft, int rows, int cols, int block_w, int block_h, int gutter)
{
    for(int i = 0; i < rows; i++) {
        vector<Block> row;

        double y = topLeft.y - i * (block_h + gutter) - block_h;

        for(int j = 0; j < cols; j++) {
            double x = topLeft.x + j * (block_w + gutter);
            Block b(Point2D(x, y), block_w, block_h);

            row.push_back(b);
        }

        blocks.push_back(row);
    }
};

void Blocks::draw() {
    for(unsigned int i = 0; i < blocks.size(); i++) {
        for(unsigned int j = 0; j < blocks[i].size(); j++) {
            blocks[i][j].draw();
        }
    }
}

void Blocks::checkCollisions(Ball* ball) {
    for(unsigned int i = 0; i < blocks.size(); i++) {
        for(unsigned int j = 0; j < blocks[i].size(); j++) {
            blocks[i][j].collideWithBall(ball);
        }
    }
}
