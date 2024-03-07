#pragma once
#include <GL/glut.h>
#include <iostream>
#include <numbers>

class Sprite {
public:
    Sprite(float startX, float startY);
    void draw(float cameraX, float cameraY);

    // position
    float x;
    float y;

    float radius = 5.0f;

};