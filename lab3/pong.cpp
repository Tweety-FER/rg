#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include "point2d.cpp"
#include <string>
#include <iostream>

    //Windows support
#ifdef __WIN32
#include <windows.h>
#endif

#ifndef DIMS
        #define DIMS 1
        #define WIN_WIDTH 800
        #define WIN_HEIGHT 500
        #define WIN_POS_X 100
        #define WIN_POS_Y 100
        #define PADDLE_WIDTH 15
        #define PADDLE_HEIGHT 60
        #define PADDLE_SPEED 4.0f
        #define LEFT_PADDLE_X 10.0f
        #define RIGHT_PADDLE_X (WIN_WIDTH - PADDLE_WIDTH - LEFT_PADDLE_X)
        #define PADDLE_Y (WIN_HEIGHT / 2.0f - PADDLE_HEIGHT / 2.0f)
        #define BALL_MAX_V 2.0f
        #define BALL_INITIAL_V_X (- BALL_MAX_V)
        #define BALL_INITIAL_V_Y (0.0f)
        #define PADDLE_TOL (PADDLE_HEIGHT / 4.0)
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

        int scorePlayer = 0
          , scoreAI = 0;

        Point2D myPaddle(LEFT_PADDLE_X, PADDLE_Y)
              , aiPaddle(RIGHT_PADDLE_X, PADDLE_Y)
              , ball(WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f)
              , ballVelocity(BALL_INITIAL_V_X, BALL_INITIAL_V_Y);

        /*---------------------------------------------*/
        void reshapeHandler(int width, int height);
        void displayHandler();
        void tickHandler(int time);
        void drawSquare(float x, float y, float w, float h);
        void drawPaddles();
        void moveBall();
        void drawBall();
        void moveAI();
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

            window = glutCreateWindow("Pong");

            //Set up the handlers
            //glutReshapeFunc(reshapeHandler);
            glutTimerFunc(framerate, tickHandler, 0);
            glutDisplayFunc(displayHandler);
            glutKeyboardFunc(keypressHandler);
            
            set2DMode(width, height);
            glColor3f(1.0f, 1.0f, 1.0f); //Draw in white


            glutMainLoop();
            return 0;
        }

        void drawSquare(float x, float y, float w, float h) {
            glBegin(GL_QUADS);
                glVertex2f(x, y);
                glVertex2f(x + w, y);
                glVertex2f(x + w, y + h);
                glVertex2f(x, y + h);
            glEnd();
        }

        void drawPaddles() {
            drawSquare(myPaddle.x, myPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT);
            drawSquare(aiPaddle.x, aiPaddle.y, PADDLE_WIDTH, PADDLE_HEIGHT);
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
            moveAI();
            glutTimerFunc(framerate, tickHandler, 0);
            glutPostRedisplay();
        }

        void drawText(float x, float y, std::string text) {
            glRasterPos2f(x, y);
            glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*) text.c_str());
        }

        void moveBall() {
            ball.x += ballVelocity.x;
            ball.y += ballVelocity.y;

            //Collision with left wall
            if(ball.x < 0) {
                scoreAI++;
                ball.x = WIN_WIDTH / 2.0f;
                ball.y = WIN_HEIGHT / 2.0f;
                ballVelocity.x = fabs(BALL_INITIAL_V_X);
                ballVelocity.y = BALL_INITIAL_V_Y;
            }
            
            //Collision with right wall
            if(ball.x > WIN_WIDTH) {
                scorePlayer++;
                ball.x = WIN_WIDTH / 2.0f;
                ball.y = WIN_HEIGHT / 2.0f;
                ballVelocity.x = BALL_INITIAL_V_X;
                ballVelocity.y = BALL_INITIAL_V_Y;
            }

            bool leftCol =  ball.x >= 0
                         && ball.x <= LEFT_PADDLE_X + PADDLE_WIDTH
                         && BETWEEN(ball.y, myPaddle.y, myPaddle.y + PADDLE_HEIGHT);

            bool rightCol =  ball.x <= WIN_WIDTH
                          && ball.x >= RIGHT_PADDLE_X
                          && BETWEEN(ball.y, aiPaddle.y, aiPaddle.y + PADDLE_HEIGHT);

            //Collision with paddle
            if(leftCol || rightCol) {
                //Swap direction
                ballVelocity.x = - ballVelocity.x;
                //Bounce y in range [-BALL_MAX_V, +BALL_MAX_V]
                ballVelocity.y = BALL_MAX_V * 2 * (((ball.y - myPaddle.y) / PADDLE_HEIGHT) - 0.5f);
            }

            //Collision with top/bottom wall
            if(ball.y < 0 || ball.y > WIN_HEIGHT) {
                ballVelocity.y = -ballVelocity.y;
            }
        }

        void drawBall() {
            glPointSize(3.0f);
            glBegin(GL_POINTS);
            glVertex2f(ball.x, ball.y);
            glEnd();
        }

        /**
         * Handles the window resize.
         *
         * @param width:int - New window width
         * @param height:int - New window height
         */
        void reshapeHandler(int w, int h) {
            width = w;
            height = h;

            glViewport(0, 0, width, height);
            glClearDepth(1.0f);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            glDepthFunc(GL_LESS);
        }

        void moveAI() {
            if(ball.y > aiPaddle.y + (PADDLE_HEIGHT / 2.0f) + PADDLE_TOL) {
                aiPaddle.y = MIN(aiPaddle.y + PADDLE_SPEED, WIN_HEIGHT - PADDLE_HEIGHT);
            } else if(ball.y < aiPaddle.y + (PADDLE_HEIGHT / 2.0f) - PADDLE_TOL) {
                aiPaddle.y = MAX(aiPaddle.y - PADDLE_SPEED, 0.0f);
            }
        }

        void displayHandler() {
           glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
           glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
           glLoadIdentity();

           drawText(width / 2 - 10, height - 15, to_string(scorePlayer) + ":" + to_string(scoreAI));
           drawPaddles();
           drawBall();

           glutSwapBuffers();
        }

        void keypressHandler(unsigned char key, int mouseX, int mouseY) {
            switch(key) {
                case 'w':
                    myPaddle.y = MIN(myPaddle.y + PADDLE_SPEED, WIN_HEIGHT - PADDLE_HEIGHT);
                    break;
                case 's' :
                    myPaddle.y = MAX(myPaddle.y - PADDLE_SPEED, 0.0f);
                break;
            default:
                break;
        }

        glutPostRedisplay();
    }

