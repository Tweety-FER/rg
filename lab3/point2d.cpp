using namespace std;

struct Point2D {
    float x;
    float y;

    Point2D(float a, float b) {
        x = a;
        y = b;
    }
    
    void move(Point2D offset) {
        x += offset.x;
        y += offset.y;
    }

};
