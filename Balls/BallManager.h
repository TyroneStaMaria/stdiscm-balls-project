#pragma once
#include <vector>
#include "Ball.h"

class BallManager{
public:
    static void addBall(const Ball& ball);
    static void updateBalls();
    static void drawBalls();

private:
    static std::vector<Ball> balls;

};

