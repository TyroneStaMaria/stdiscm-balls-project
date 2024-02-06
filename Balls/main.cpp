#include <GL/glut.h> // Include the GLUT header file
#include <iostream>
#include <numbers>
#include "Ball.h"
#include "BallManager.h"
#include <random>




std::random_device rd;  // Obtain a random number from hardware
std::mt19937 eng(rd()); // Seed the generator

std::uniform_real_distribution<> distrX(-1.0, 1.0); // Define range for x
std::uniform_real_distribution<> distrY(-1.0, 1.0); // Define range for y
std::uniform_real_distribution<> distrDX(-0.1, 0.1); // Define range for dx
std::uniform_real_distribution<> distrDY(-0.1, 0.1); // Define range for dy


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    BallManager::drawBalls(); // Draw all balls
    BallManager::drawWalls();

    glutSwapBuffers();
}

void update(int value) {
    BallManager::updateBalls(); // Update all balls

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // Schedule the next update
}


int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("OpenGL Bouncing Ball with Class");

    for (int i = 0; i < 2; i++) {
        float randomX = distrX(eng);
        float randomY = distrY(eng);
        float randomDX = distrDX(eng);
        float randomDY = distrDY(eng);

        BallManager::addBall(Ball(randomX, randomY, randomDX, randomDY));
    }

    BallManager::addWall(Wall(-0.5f, -0.5f, -0.5f, 0.5f));

   

    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glutMainLoop();
    return 0;
}
