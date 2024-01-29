#include "Ball.h"

Ball::Ball(float startX, float startY, float startDx, float startDy) 
    : x(startX), y(startY), dx(startDx), dy(startDy) {}


void Ball::draw() {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 0.0, 0.0); // Red color
    glVertex2f(x, y); // Center of circle
    for (int i = 0; i <= 20; i++) {
        glVertex2f(
            x + (0.1 * cos(i * 2.0 * PI / 20)),
            y + (0.1 * sin(i * 2.0 * PI / 20))
        );
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