#pragma once
#include <GL/glut.h>
#include "renderable.cpp"
#include "segment.cpp"

//Windows support
#ifdef __WIN32
#include <windows.h>
#endif

#ifndef DIMS
    #define DIMS 1
    #define WIN_WIDTH 500
    #define WIN_HEIGHT 500
    #define WIN_POS_X 100
    #define WIN_POS_Y 100
#endif

    GLuint window;
    GLuint width = WIN_WIDTH,
           height = WIN_HEIGHT;
    Renderable r;
    Point ociste(0, 0, 6.5);
    Point initial(0.0, 0.0, 1.0); //Initial orientation
    Point os;
    Point moveV;
    Point trSize;

    double angleDeg = 0;

    vector<BSpline> path;
    unsigned int last_point = 0;

    /*---------------------------------------------*/
    void reshapeHandler(int width, int height);
    void displayHandler();
    void updatePerspective();
    void keypressHandler(unsigned char key, int mouseX, int mouseY);
    void drawAxes();
    void moveObj();
    void drawSpiral();
    void drawTangents();
    /*---------------------------------------------*/

    int main(int argc, char** argv) {
        //Init block
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowSize(width, height);
        glutInitWindowPosition(WIN_POS_X, WIN_POS_Y);
        glutInit(&argc, argv);

        //Read the object
        r.read("objects/f16.obj");
        r.normalize();
        r.center();
        path = readMoves("paths/spiral.path", 0.01, false);
        moveObj(); //Position the object for the initial showing

        //Create an appropriately named window
        window = glutCreateWindow(r.getName().c_str());

        //Set up the handlers
        glutReshapeFunc(reshapeHandler);
        glutDisplayFunc(displayHandler);
        glutKeyboardFunc(keypressHandler);

        glutMainLoop();
        return 0;
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
        updatePerspective();
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
        glDepthFunc(GL_LESS);
    }

    /**
     * Refresh the perspective
     */
    void updatePerspective() {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, (float) width/height, 0.5, 8.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(ociste.x, ociste.y, ociste.z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    }

    void displayHandler() {
       glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       drawAxes();
       drawSpiral();
       drawTangents();

       glPushMatrix();
       glTranslated(moveV.x, moveV.y, moveV.z);
       glRotated(angleDeg, os.x, os.y, os.z);
       r.render();

       glPopMatrix();
       glutSwapBuffers();
    }

    void keypressHandler(unsigned char key, int mouseX, int mouseY) {
        switch(key) {
            case 'w':
                ociste.y += 0.1;
                break;
            case 's' :
                ociste.y -= 0.1;
                break;
            case 'a' :
                ociste.x -= 0.1;
                break;
            case 'd' :
                ociste.x += 0.1;
                break;
            case 'q' :
                ociste.z += 0.1;
                break;
            case 'e' :
                ociste.z -= 0.1;
                break;
            case 'm' :
                moveObj();
                break;
            case 'r' :
                ociste.x = 0;
                ociste.y = 0;
                ociste.z = 5;
                break;
            default:
                cout << "No handler for this key" << endl;
        }

        updatePerspective();
        glutPostRedisplay();
    }

    void drawSpiral() {
        unsigned int i;

        //Draw spiral
        glBegin(GL_LINES);
        glColor3ub(255, 0, 255);
        glLineWidth(10.0f);
        for(i = 0; i < path.size(); i++) {
            glVertex3d(path[i].point.x, path[i].point.y, path[i].point.z);
        }
        glLineWidth(1.0f);
        glEnd();


    }

void drawTangents() {
    unsigned int i;

    //Draw the tangents
    for(i = 0; i < path.size(); i++) {
        Point p = path[i].point;
        Point t = path[i].tangent * 0.25;
        Point m = p + t;

        glBegin(GL_LINES);
        glColor3ub(0, 200, 100);
        glVertex3d(p.x, p.y, p.z);
        glVertex3d(m.x, m.y, m.z);
        glEnd();
    }

}

void drawAxes() {
    //X
    glBegin(GL_LINES);
        glColor3ub(255, 0, 0);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(1.0f, 0.0f, 0.0f);
    glEnd();

    //Y
    glBegin(GL_LINES);
        glColor3ub(0, 255, 0);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();

    //Z
    glBegin(GL_LINES);
        glColor3ub(0, 0, 255);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(0.0f, 0.0f, 1.0f);
    glEnd();
}

void moveObj() {
    if(last_point == path.size()) {
        cout << "Out of moves" << endl;
        return; //No more moves
    }

    if(last_point > 0) {
      trSize = path[last_point].point - path[last_point - 1].point;
    } else {
      trSize = path[0].point - initial;
    }

    Point p = path[last_point].point;
    Point t = path[last_point++].tangent;
    Point e = t - p;
    os = initial.cross(e);
    angleDeg = initial.angle(e);
    moveV = p;
 }
