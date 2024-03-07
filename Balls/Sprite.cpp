#include "Sprite.h"

Sprite::Sprite(float startX, float startY)
    : x(startX), y(startY) {
}


void Sprite::draw() {
    glBegin(GL_TRIANGLES); // Start drawing a triangle
    glColor3ub(157, 193, 131); // Set color to green

    // Vertex 1 (You can adjust these coordinates as needed)
    glVertex2f(x, y);
    // Vertex 2
    glVertex2f(x + 10.0f, y + 10.0f); // Adjust these to control the size and shape of your triangle
    // Vertex 3
    glVertex2f(x - 10.0f, y + 10.0f);

    glEnd(); // End drawing
}