#include "Sprite.h"

Sprite::Sprite(float startX, float startY)
    : x(startX), y(startY) {
}


void Sprite::draw(float cameraX, float cameraY) {
    glBegin(GL_TRIANGLES); // Start drawing a triangle
    glColor3ub(157, 193, 131); // Set color to green

    glVertex2f(x - cameraX, y - cameraY);
    glVertex2f(x + 10.0f - cameraX, y + 10.0f - cameraY);
    glVertex2f(x - 10.0f - cameraX, y + 10.0f - cameraY);

    glEnd(); // End drawing
}