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
    void invertDirection(bool collideX, bool collideY);
    // position
    float x;
    float y;

    // velocity 
    float dx;
    float dy;

    float radius = 0.01f;

};

