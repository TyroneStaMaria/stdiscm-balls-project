#pragma once
#include <GL/glut.h>
#include <iostream>
#include <numbers>

class Sprite {
public:
    Sprite(float startX, float startY);
    void draw();

    // position
    float x;
    float y;

    float radius = 5.0f;

};