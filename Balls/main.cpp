// Balls.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <GL/glut.h> // Include the GLUT header file
#include <iostream>
#include <numbers>
#include "Ball.h"
#include "BallManager.h"


//Ball ball(0.0f, 0.0f, 0.05f, 0.07f); // Initial position and velocity


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    BallManager::drawBalls(); // Draw all balls

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
    glutCreateWindow("OpenGL Bouncing Ball with Class");

    BallManager::addBall(Ball(0.0f, 0.0f, 0.05f, 0.07f));
    BallManager::addBall(Ball(0.2f, 0.1f, 0.03f, 0.06f));
    BallManager::addBall(Ball(0.1f, 0.5f, 0.1f, 0.2f));


    glutDisplayFunc(display);
    glutTimerFunc(25, update, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glutMainLoop();
    return 0;
}
