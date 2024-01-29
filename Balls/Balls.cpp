// Balls.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <GL/glut.h> // Include the GLUT header file
#include <iostream>
#include <numbers>

const double PI = std::numbers::pi;


float ballX = 0.0f;
float ballY = 0.0f;
float ballXDir = 0.05f;
float ballYDir = 0.07f;

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer
    glLoadIdentity(); // Reset transformations

    // Draw the ball
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 0.0, 0.0); // Red color
    glVertex2f(ballX, ballY); // Center of circle
    for (int i = 0; i <= 20; i++) {
        glVertex2f(
            ballX + (0.1 * cos(i * 2.0 * PI / 20)),
            ballY + (0.1 * sin(i * 2.0 * PI / 20))
        );
    }
    glEnd();

    glutSwapBuffers(); // Swap the front and back frame buffers (double buffering)
}

void update(int value) {
    ballX += ballXDir;
    ballY += ballYDir;

    if (ballX > 1.0 || ballX < -1.0) {
        ballXDir *= -1; // Reverse direction
    }
    if (ballY > 1.0 || ballY < -1.0) {
        ballYDir *= -1; // Reverse direction
    }

    glutPostRedisplay(); // Redraw the scene
    glutTimerFunc(16, update, 0); // Schedule next update after 16 ms
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Enable double buffering and RGB color mode
    glutCreateWindow("OpenGL Bouncing Ball"); // Create a window with the given title
    glutDisplayFunc(display); // Register display callback function
    glutTimerFunc(25, update, 0); // Set the timer to call the update function

    // Set up your projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set the Cartesian coordinates

    glutMainLoop(); // Enter the GLUT event processing loop
    return 0;

}





// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
