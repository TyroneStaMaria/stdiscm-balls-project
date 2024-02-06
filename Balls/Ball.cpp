#include "Ball.h"

Ball::Ball(float startX, float startY, float startDx, float startDy) 
    : x(startX), y(startY), dx(startDx), dy(startDy) {}


void Ball::draw() {
    float radius = 0.01f;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 0.0, 0.0); // Red color
    glVertex2f(x, y); // Center of circle
    for (int i = 0; i <= 20; i++) {
        float angle = 2.0f * PI * float(i) / float(20);  // Calculate the angle
        float xComponent = radius * cosf(angle); // Calculate the x component
        float yComponent = radius * sinf(angle); // Calculate the y component

        glVertex2f(x + xComponent, y + yComponent);
    }
    glEnd();
}

void Ball::move() {
    x += dx;
    y += dy;

    // Check for wall collisions and reverse velocity if necessary
    if (x > 1.0 || x < -1.0) dx *= -1;
    if (y > 1.0 || y < -1.0) dy *= -1;

}

void Ball::invertDirection(bool collideX, bool collideY) {
    if (collideX) dx *= -1;
    if (collideY) dy *= -1;
}