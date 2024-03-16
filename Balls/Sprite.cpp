#include "Sprite.h"

Sprite::Sprite()
    : x(0), y(0) { // Initializes x and y to some default value, e.g., 0
}

Sprite::Sprite(float startX, float startY)
    : x(startX), y(startY) {

    std::cout << x << " " << y << std::endl;
}

void Sprite::draw(float cameraX, float cameraY) {
    glBegin(GL_QUADS);

    glColor3ub(157, 193, 131);

    // Top vertex
    glVertex2f(x, y + 10.0f);
    // Right vertex
    glVertex2f(x + 10.0f, y);
    // Bottom vertex
    glVertex2f(x, y - 10.0f);
    // Left vertex
    glVertex2f(x - 10.0f, y);

    glEnd();
}

void Sprite::moveUp(float amount) {
    y += amount;
}

void Sprite::moveDown(float amount) {
    y -= amount;
}

void Sprite::moveLeft(float amount) {
    x -= amount;
}

void Sprite::moveRight(float amount) {
    x += amount;
}

float Sprite::getX() const {
    return x; // Return the private member variable x
}

float Sprite::getY() const {
    return y; // Return the private member variable y
}

void Sprite::setX(float num){
    x = num;
}

void Sprite::setY(float num){
    y = num;
}