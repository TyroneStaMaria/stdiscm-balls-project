#pragma once
#include <GL/glut.h>
#include <iostream>
#include <numbers>

const double PI = std::numbers::pi;

class Ball{
    public: 
        Ball(float startX, float startY, float startDx, float startDy);
        void draw();
        void move();
    private:
        // position
        float x;
        float y;

        // velocity 
        float dx;
        float dy;
    //public:
        //float x, y; // Position of the ball
        //float dx, dy; // Velocity of the ball

        /*Ball(float startX, float startY, float startDx, float startDy)
            : x(startX), y(startY), dx(startDx), dy(startDy) {}*/

        //void draw() {
            
        //}

        //void move() {
        //    x += dx;
        //    y += dy;

        //    // Check for wall collisions and reverse velocity if necessary
        //    if (x > 1.0 || x < -1.0) dx *= -1;
        //    if (y > 1.0 || y < -1.0) dy *= -1;
        //}
};

