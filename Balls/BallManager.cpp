#include "BallManager.h"
#include "Wall.h"

std::vector<Ball> BallManager::balls;
std::vector<Wall> BallManager::walls;

void BallManager::addBall(const Ball& ball) {
    balls.push_back(ball);
}

void BallManager::updateBalls() {
    for (auto& ball : balls) {

        for (const auto& wall : walls) {
            bool collideX = false, collideY = false;

            // For vertical walls, ensure the ball is within the y range of the wall
            if (wall.x1 == wall.x2) {
                float nextX = ball.x + ball.dx;
                if (nextX - ball.radius <= wall.x1 && nextX + ball.radius >= wall.x1 &&
                    ball.y >= std::min(wall.y1, wall.y2) && ball.y <= std::max(wall.y1, wall.y2)) {
                    collideX = true;
                }
            }

            // For horizontal walls, ensure the ball is within the x range of the wall
            if (wall.y1 == wall.y2) {
                float nextY = ball.y + ball.dy;
                if (nextY - ball.radius <= wall.y1 && nextY + ball.radius >= wall.y1 &&
                    ball.x >= std::min(wall.x1, wall.x2) && ball.x <= std::max(wall.x1, wall.x2)) {
                    collideY = true;
                }
            }

            if (collideX || collideY) {
                // Invert direction only if collision is detected
                ball.invertDirection(collideX, collideY);
            }
        }

        ball.move(); // Move the ball first to check its new position against the wall
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