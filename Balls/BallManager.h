#pragma once
#include <vector>
#include "Ball.h"
#include "Point.h"
using namespace std; 

class BallManager{
public:
    static void addBall(const Ball& ball);
    static void updateBalls(float deltaTime, float leftBoundary, float rightBoundary, float topBoundary, float bottomBoundary);
    static void drawBalls();
    static void addBallsDistance(int n, Point start, Point end, float velocity, float angle, int startSpawn, int endSpawn);
    static void addBallsAngle(int n, Point start, float velocity, float startAngle, float endAngle, int startSpawn, int endSpawn);
    static void addBallsVelocity(int n, Point position, float startVelocity, float endVelocity, float angle, int startSpawn, int endSpawn);
    static vector<Ball> getBalls();
    static void updateRange(int start, int end, float deltaTime, float leftBoundary, float rightBoundary, float topBoundary, float bottomBoundary);

private:
    static vector<Ball> balls;
};

