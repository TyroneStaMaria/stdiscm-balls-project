#include "BallManager.h"
#include "Wall.h"

#include <thread>
#include <mutex>

using namespace std;


vector<Ball> BallManager::balls;
vector<Wall> BallManager::walls;


void BallManager::addBall(const Ball& ball) {
    balls.push_back(ball);
}

void BallManager::updateBalls(float deltaTime) {

    const size_t numThreads = thread::hardware_concurrency();
    vector<thread> threads(numThreads);
    size_t ballsPerThread = balls.size() / numThreads;

    auto updateRange = [](int start, int end, float deltaTime) {
        for (int i = start; i < end; i++) {
            // Calculate the ball's next position based on its current velocity components
            float nextX = balls[i].x + balls[i].dx * deltaTime;
            float nextY = balls[i].y + balls[i].dy * deltaTime;
            balls[i].checkCanvasCollision();


            for (const auto& wall : walls) {
                bool collideX = false, collideY = false;

                // Adjusted collision detection for vertical walls
                
                if (wall.point1.x == wall.point2.x && nextX - balls[i].radius <= wall.point1.x && nextX + balls[i].radius >= wall.point1.x &&
                    balls[i].y >= std::min(wall.point1.y, wall.point2.y) && balls[i].y <= std::max(wall.point1.y, wall.point2.y)) {
                    collideX = true;
                }

                // Adjusted collision detection for horizontal walls
                if (wall.point1.y == wall.point2.y && nextY - balls[i].radius <= wall.point1.y && nextY + balls[i].radius >= wall.point1.y &&
                    balls[i].x >= std::min(wall.point1.x, wall.point2.x) && balls[i].x <= std::max(wall.point1.x, wall.point2.x)) {
                    collideY = true;
                }

                //if (wall.x1 == wall.x2 && nextX - balls[i].radius <= wall.x1 && nextX + balls[i].radius >= wall.x1 &&
                //    balls[i].y >= std::min(wall.y1, wall.y2) && balls[i].y <= std::max(wall.y1, wall.y2)) {
                //    collideX = true;
                //}

                //// Adjusted collision detection for horizontal walls
                //if (wall.y1 == wall.y2 && nextY - balls[i].radius <= wall.y1 && nextY + balls[i].radius >= wall.y1 &&
                //    balls[i].x >= std::min(wall.x1, wall.x2) && balls[i].x <= std::max(wall.x1, wall.x2)) {
                //    collideY = true;
                //}

                // Invert direction based on collision detection
                if (collideX || collideY) {
                    balls[i].invertDirection(collideX, collideY);
                }
            }

            // Move the ball after checking for collisions
            balls[i].move(deltaTime);
        }
    };

    for (int i = 0; i < numThreads; ++i) {
        int start = i * ballsPerThread;
        int end = (i + 1 == numThreads) ? balls.size() : (i + 1) * ballsPerThread;
        threads[i] = std::thread(updateRange, start, end, deltaTime);
    }

    for (auto& thread : threads) {
        thread.join(); // Wait for all threads to finish
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

vector<Ball> BallManager::getBalls() {
    return balls;
}