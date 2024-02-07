#include "BallManager.h"
#include "Wall.h"

std::vector<Ball> BallManager::balls;
std::vector<Wall> BallManager::walls;

void BallManager::addBall(const Ball& ball) {
    balls.push_back(ball);
}

void BallManager::updateBalls(float deltaTime) {
    for (auto& ball : balls) {
        // Calculate the ball's next position based on its current velocity components
        float nextX = ball.x + ball.dx * deltaTime;
        float nextY = ball.y + ball.dy * deltaTime;
        ball.checkCanvasCollision();


        for (const auto& wall : walls) {
            bool collideX = false, collideY = false;

            // Adjusted collision detection for vertical walls
            if (wall.x1 == wall.x2 && nextX - ball.radius <= wall.x1 && nextX + ball.radius >= wall.x1 &&
                ball.y >= std::min(wall.y1, wall.y2) && ball.y <= std::max(wall.y1, wall.y2)) {
                collideX = true;
            }

            // Adjusted collision detection for horizontal walls
            if (wall.y1 == wall.y2 && nextY - ball.radius <= wall.y1 && nextY + ball.radius >= wall.y1 &&
                ball.x >= std::min(wall.x1, wall.x2) && ball.x <= std::max(wall.x1, wall.x2)) {
                collideY = true;
            }

            // Invert direction based on collision detection
            if (collideX || collideY) {
                ball.invertDirection(collideX, collideY);
            }
        }

        // Move the ball after checking for collisions
        ball.move(deltaTime);
    }
}



void BallManager::drawBalls() {
    for (auto& ball : balls) {
        ball.draw();
    }
}

void BallManager::addWall(const Wall& wall) {
    walls.push_back(wall);
}

void BallManager::drawWalls() {
    for (const auto& wall : walls) {
        wall.draw();
    }
}