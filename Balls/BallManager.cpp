#include "BallManager.h"

std::vector<Ball> BallManager::balls;

void BallManager::addBall(const Ball& ball) {
    balls.push_back(ball);
}

void BallManager::updateBalls() {
    for (auto& ball : balls) {
        ball.move();
    }
}

void BallManager::drawBalls() {
    for (auto& ball : balls) {
        ball.draw();
    }
}
