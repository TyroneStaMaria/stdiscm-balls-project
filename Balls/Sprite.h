#pragma once
#include <GL/glut.h>
#include <iostream>
#include <numbers>

class Sprite {
public:
    Sprite(); 
    Sprite(float startX, float startY);
    void draw(float cameraX, float cameraY);

    void moveUp(float amount);
    void moveDown(float amount);
    void moveLeft(float amount);
    void moveRight(float amount);
    float getX() const; 
    float getY() const; 

    void setX(float num);
    void setY(float num);

private:
    float x;
    float y;
    float height = 10.0f; 
    float radius = 5.0f;
};