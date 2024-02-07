#pragma once
#include <GL/glut.h>
#include <iostream>
#include <numbers>

const double PI = std::numbers::pi;

class Ball{
public: 
    Ball(float startX, float startY, float velocity, float startAngle);
    void draw();
    void move(float deltaTime);
    void invertDirection(bool collideX, bool collideY);
    void normalizeVelocity();
    void checkCanvasCollision();
    // position
    float x;
    float y;

    float velocity;
    float angle;

    float dx;
    float dy;

    float radius = 0.01f;

};

