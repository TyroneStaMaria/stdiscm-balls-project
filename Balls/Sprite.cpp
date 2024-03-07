#include "Sprite.h"

Sprite::Sprite(float startX, float startY)
    : x(startX), y(startY) {
}


void Sprite::draw(float cameraX, float cameraY) {
    glBegin(GL_QUADS);

    glColor3ub(157, 193, 131);

    // Top vertex
    glVertex2f(x - cameraX, y + 10.0f - cameraY);
    // Right vertex
    glVertex2f(x + 10.0f - cameraX, y - cameraY);
    // Bottom vertex
    glVertex2f(x - cameraX, y - 10.0f - cameraY);
    // Left vertex
    glVertex2f(x - 10.0f - cameraX, y - cameraY);

    glEnd();
}