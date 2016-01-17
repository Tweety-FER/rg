#pragma once
#include <fstream>
#include <GL/gl.h>
#include <sstream>

using namespace std;

class Face {
    public:
        int a;
        int b;
        int c;

        void parse(stringstream& ss);
};

void Face::parse(stringstream& ss) {
    ss >> a >> b >> c;
}
