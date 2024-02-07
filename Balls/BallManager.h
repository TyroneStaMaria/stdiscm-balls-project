#pragma once
#include <vector>
#include "Wall.h"
#include "Ball.h"

class BallManager{
public:
    static void addBall(const Ball& ball);
    static void addWall(const Wall& wall);
    static void updateBalls(float deltaTime);
    static void drawBalls();
    static void drawWalls();

private:
    static std::vector<Ball> balls;
    static std::vector<Wall> walls;
};

