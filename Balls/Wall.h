// Wall.h
#pragma once

#include <GL/glut.h>

class Wall {
public:
    float x1, y1, x2, y2; // Endpoints of the wall

    Wall(float x1, float y1, float x2, float y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}

    void draw() const {
        glColor3f(1.0, 1.0, 0.0);
        glLineWidth(2.0f);
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
    }
};
