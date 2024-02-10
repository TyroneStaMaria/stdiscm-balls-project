#pragma once
#include <vector>
#include "Wall.h"
#include "Ball.h"

using namespace std; 

class BallManager{
public:
    static void addBall(const Ball& ball);
    static void addWall(const Wall& wall);
    static void updateBalls(float deltaTime);
    static void drawBalls();
    static void drawWalls();
    static vector<Ball> getBalls();

private:
    static vector<Ball> balls;
    static vector<Wall> walls;
};

