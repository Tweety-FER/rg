#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include "ball.h"
#include "paddle.h"
#include "blocks.h"
#include <string>
#include <iostream>

//Windows support (in theory)
#ifdef __WIN32
#include <windows.h>
#endif

#ifndef DIMS
        #define DIMS 1
        #define WIN_WIDTH 790
        #define WIN_HEIGHT 600
        #define WIN_POS_X 100
        #define WIN_POS_Y 100
        #define PADDLE_WIDTH 100
        #define PADDLE_HEIGHT 15
        #define PADDLE_OFFSET 10
        #define PADDLE_SPEED 9
        #define BALL_MAX_V 2.0f
        #define BALL_INITIAL_V_Y (- BALL_MAX_V)
        #define BALL_INITIAL_V_X (0.0f)
        #define BALL_RADIUS 3.0f
        #define BLOCK_WIDTH 71
        #define BLOCK_HEIGHT 20
        #define BLOCK_GUTTER 1
        #define BLOCK_COLS 11
        #define BLOCK_ROWS 8
#endif

#define MIN(x, y) ((x) < (y) ? (x) : (y))
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define BETWEEN(v, x, y) (((v) >= (x)) && ((v) <= (y)))
#define fabs(x) ((x) > 0 ? (x) : (- (x)))

    using namespace std;

        GLuint window;
        GLuint width = WIN_WIDTH,
               height = WIN_HEIGHT,
               framerate = 1000 / 60;

        Blocks* blocks = new Blocks( Point2D(0, WIN_HEIGHT)
                                   , BLOCK_ROWS
                                   , BLOCK_COLS
                                   , BLOCK_WIDTH
                                   , BLOCK_HEIGHT
                                   , BLOCK_GUTTER);

        Ball* ball = new Ball( Point2D(WIN_WIDTH / 2.0, WIN_HEIGHT / 2.0)
                             , Point2D(BALL_INITIAL_V_X, BALL_INITIAL_V_Y)
                             , BALL_RADIUS
                             );

        Paddle* paddle = new Paddle( Point2D(WIN_WIDTH / 2.0 - PADDLE_WIDTH / 2.0, PADDLE_OFFSET)
                                   , PADDLE_WIDTH
                                   , PADDLE_HEIGHT
                                   , PADDLE_SPEED
                                   );
                /*---------------------------------------------*/
        void reshapeHandler(int width, int height);
        void displayHandler();
        void tickHandler(int time);
        void moveBall();
        void set2DMode(int width, int height);
        void drawScore(float x, float y, std::string text);
        void keypressHandler(unsigned char key, int mouseX, int mouseY);
        /*---------------------------------------------*/

        int main(int argc, char** argv) {
            //Init block
            glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
            glutInitWindowSize(width, height);
            glutInitWindowPosition(WIN_POS_X, WIN_POS_Y);
            glutInit(&argc, argv);

            window = glutCreateWindow("Other game");

            //Set up the handlers
            //glutReshapeFunc(reshapeHandler);
            glutTimerFunc(framerate, tickHandler, 0);
            glutDisplayFunc(displayHandler);
            glutKeyboardFunc(keypressHandler);
            
            set2DMode(width, height);

            glutMainLoop();
            return 0;
        }

        void set2DMode(int width, int height) {
            glViewport(0, 0, width, height);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
        }   

        void tickHandler(int time) {
            moveBall();
            glutTimerFunc(framerate, tickHandler, 0);
            glutPostRedisplay();
        }

        void drawText(float x, float y, std::string text) {
            glRasterPos2f(x, y);
            glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*) text.c_str());
        }

        void moveBall() {
            ball->move();

            double x = ball->getPosition().x;
            double y = ball->getPosition().y;
            double r = ball->getRadius();
            Point2D v = ball->getVelocity();

            //Hit left or right wall
            if(x - r <= 0 || x + r >= WIN_WIDTH) {
                ball->setVelocity(Point2D(-v.x, v.y));
            }

            //Hit top wall
            if(y + r >= WIN_HEIGHT || y - r <= 0) {
                ball->setVelocity(Point2D(v.x, -v.y));
            }

            //Hit paddle
            bool hitPaddle = y - r >= paddle->getPosition().y
                          && y + r <= paddle->getPosition().y + paddle->getHeight()
                          && x - r >= paddle->getPosition().x
                          && x + r <= paddle->getPosition().x + paddle->getWidth();

            if(hitPaddle) {
                double vx = BALL_MAX_V * 2 * (((x - paddle->getPosition().x) / PADDLE_WIDTH) - 0.5f);

                ball->setVelocity(Point2D(vx, -v.y));
            }
            
            blocks->checkCollisions(ball);
        }

        
        void displayHandler() {
           glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
           glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
           glLoadIdentity();

           //drawText(width / 2 - 10, height - 15, to_string(scorePlayer) + ":" + to_string(scoreAI));
           ball->draw();
           paddle->draw();
           blocks->draw();

           glutSwapBuffers();
        }

        void keypressHandler(unsigned char key, int mouseX, int mouseY) {
            switch(key) {
                case 'a':
                    if(paddle->getPosition().x >= PADDLE_SPEED) {
                      paddle->moveLeft();
                    }
                    break;
                case 'd' :
                    if(paddle->getPosition().x + paddle->getWidth() <= WIN_WIDTH - PADDLE_SPEED) {
                        paddle->moveRight();
                    }
                    break;
            default:
                break;
        }

        glutPostRedisplay();
    }

