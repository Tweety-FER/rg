#pragma once
#include "face.cpp"
#include <fstream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include "point.cpp"
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Renderable {
    protected:
        string name;
        vector<Point> points;
        vector<Face>  faces;
    public:
        //Default to the name "Shape"
        Renderable() : name("Shape") {};
        void read(string file_name);
        void normalize();
        void center();
        void render();
        void print_debug();
        string getName() {
            return name;
        }
};

void Renderable::read(string file_name) {
    fstream f;
    string  line;

    f.open(file_name, ios::in);

    while(getline(f, line)) {
        //Skip empty lines and comments
        if(line.length() == 0) continue;

        stringstream ls (line);
        char token;

        ls >> token;

        if (token == 'g') {
            ls >> name;
        } else if (token == 'v') {
            Point p;
            p.parse(ls);
            points.push_back(p);
        } else if (token == 'f') {
            Face f;
            f.parse(ls);
            faces.push_back(f);
        } else if (token == '#') { 
            continue; //Comment, not interested
        }else {
            cout << "Invalid line:" << line << ", skipping" << endl;
        }
    }

    f.close();
}

void Renderable::normalize() {
    points = scale(points);
}

void Renderable::center() {
    if(points.size() == 0) return; //Nothing to center

    double min_x = points[0].x,
           min_y = points[0].y,
           min_z = points[0].z,
           max_x = points[0].x,
           max_y = points[0].y,
           max_z = points[0].z,
           mid_x, mid_y, mid_z;

    //Find bounds
    for(Point p : points) {
        if(p.x < min_x) min_x = p.x;
        if(p.y < min_y) min_y = p.y;
        if(p.z < min_z) min_z = p.z;
        if(p.x > max_x) max_x = p.x;
        if(p.y > max_y) max_y = p.y;
        if(p.z > max_z) max_z = p.z;
    }

    //Find centers
    mid_x = (min_x + max_x) / 2.0;
    mid_y = (min_y + max_y) / 2.0;
    mid_z = (min_z + max_z) / 2.0;

    //Center
    for(unsigned int i = 0; i < points.size(); i++) {
        points[i].x -= mid_x;
        points[i].y -= mid_y;
        points[i].z -= mid_z;
    }
}

void Renderable::render() {
    for(Face f : faces) {
        glBegin(GL_LINE_LOOP);
        glColor3ub(255, 255, 255);
        glVertex3f(points[f.a - 1].x, points[f.a - 1].y, points[f.a - 1].z);
        glVertex3f(points[f.b - 1].x, points[f.b - 1].y, points[f.b - 1].z);
        glVertex3f(points[f.c - 1].x, points[f.c - 1].y, points[f.c - 1].z);
        glEnd();
    }
}

void Renderable::print_debug() {
    cout << this->name << endl;

    for(Point p : points) {
        cout << "v " << p.x << " " << p.y << " " << p.z << endl; 
    }

    for(Face f : faces) {
        cout << "f " << f.a << " " << f.b << " " << f.c << endl;
    }
}
