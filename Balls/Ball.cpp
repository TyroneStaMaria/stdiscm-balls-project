#include "Ball.h"
#include <cmath>



Ball::Ball(float startX, float startY, float velocity, float startAngle)
    : x(startX), y(startY), velocity(velocity), angle(startAngle) {


        float angleRadians = startAngle * (PI / 180.0f);
        dx = velocity * std::cos(angleRadians);
        dy = velocity * std::sin(angleRadians);
    }


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

void Ball::move(float deltaTime) {
    // Predict the ball's next position based on its current velocity
    x += dx * deltaTime;
    y += dy * deltaTime;
}

void Ball::checkCanvasCollision() {
    // Check for collisions with the left or right edges of the canvas
    if (x - radius < -1.0 || x + radius > 1.0) {
        dx *= -1; // Invert the x-component of the velocity
        if (x - radius < -1.0) {
            x = -1.0 + radius; // Adjust position to avoid sticking to the edge
        }
        else {
            x = 1.0 - radius;
        }
    }

    // Check for collisions with the top or bottom edges of the canvas
    if (y - radius < -1.0 || y + radius > 1.0) {
        dy *= -1; // Invert the y-component of the velocity
        if (y - radius < -1.0) {
            y = -1.0 + radius; // Adjust position to avoid sticking to the edge
        }
        else {
            y = 1.0 - radius;
        }
    }

    // Normalize the velocity to ensure consistent speed
    normalizeVelocity();
}

void Ball::invertDirection(bool collideX, bool collideY) {
    if (collideX) {
        dx *= -1; // Invert X direction
    }
    if (collideY) {
        dy *= -1; // Invert Y direction
    }
    // Optionally, you can normalize dx and dy to ensure consistent speed
    normalizeVelocity();
}

// Ensure dx and dy maintain the original speed after any adjustments
void Ball::normalizeVelocity() {
    float velocityMagnitude = std::sqrt(dx * dx + dy * dy);
    dx = (dx / velocityMagnitude) * velocity;
    dy = (dy / velocityMagnitude) * velocity;
}