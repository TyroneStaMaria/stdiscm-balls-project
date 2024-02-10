// Wall.h
#pragma once

#include <GL/glut.h>
#include "Point.h"
using namespace std; 

class Wall {
public:
    Point point1;
    Point point2;

    Wall(Point point1, Point point2) : point1(point1), point2(point2) {}

    void draw() const {
        glColor3f(1.0f, 1.0f, 0.0f);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        glVertex2f(point1.x, point1.y);
        glVertex2f(point2.x, point2.y);
        glEnd();
    }
};
