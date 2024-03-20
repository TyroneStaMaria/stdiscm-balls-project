#include "Sprite.h"

Sprite::Sprite()
    : x(0), y(0) { 
}

Sprite::Sprite(float startX, float startY)
    : x(startX), y(startY) {

    std::cout << x << " " << y << std::endl;
}

void Sprite::draw(float cameraX, float cameraY) {
    glBegin(GL_QUADS);

    glColor3ub(157, 193, 131);

    glVertex2f(x, y + height);
    glVertex2f(x + height, y);
    glVertex2f(x, y - height);
    glVertex2f(x - height, y);

    glEnd();
}

void Sprite::moveUp(float amount) {
    height = height == 10.0f ? 7.5f : 10.0f;
    y += amount;
}

void Sprite::moveDown(float amount) {
    height = height == 10.0f ? 7.5f : 10.0f;
    y -= amount;
}

void Sprite::moveLeft(float amount) {
    height = height == 10.0f ? 7.5f : 10.0f;

    x -= amount;
}

void Sprite::moveRight(float amount) {
    height = height == 10.0f ? 7.5f : 10.0f;
    x += amount;
}

float Sprite::getX() const {
    return x; 
}

float Sprite::getY() const {
    return y; 
}

void Sprite::setX(float num){
    x = num;
}

void Sprite::setY(float num){
    y = num;
}