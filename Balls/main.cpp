#include <GL/glut.h> // Include the GLUT header file
#include <iostream>
#include <numbers>
#include <random>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glut.h"
#include "Ball.h"
#include "BallManager.h"


std::random_device rd;  // Obtain a random number from hardware
std::mt19937 eng(rd()); // Seed the generator

std::uniform_real_distribution<> distrX(-1.0, 1.0); // Define range for x
std::uniform_real_distribution<> distrY(-1.0, 1.0); // Define range for y
std::uniform_real_distribution<> distrDX(-0.1, 0.1); // Define range for dx
std::uniform_real_distribution<> distrDY(-0.1, 0.1); // Define range for dy


static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

const int MAX_WIDTH = 1920;
const int MAX_HEIGHT = 1080;

float ballX = 0.0f;
float ballY = 0.0f;
float ballAngle = 0.0f;
float ballVelocity = 0.0f;

float wallX1 = 0.0f;
float wallY1 = 0.0f;
float wallX2 = 0.0f;
float wallY2 = 0.0f;


const int targetFPS = 60;
const float targetFrameTime = 1.0f / targetFPS;
float accumulator = 0.0f;


void display() {
    // First, clear the entire window with the main background color
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    // Define the viewport and scissor box for the balls section
    GLint ballsViewportX = 0; // Starting X position
    GLint ballsViewportY = 350; // Starting Y position
    GLsizei ballsViewportWidth = 1280; // Width of the section
    GLsizei ballsViewportHeight = 720; // Height of the section

    // Enable scissor test and set the scissor box
    glEnable(GL_SCISSOR_TEST);
    glScissor(ballsViewportX, ballsViewportY, ballsViewportWidth, ballsViewportHeight);

    // Clear the balls section with a different background color
    ImVec4 ballsBgColor = ImVec4(0.2f, 0.3f, 0.4f, 1.0f); // Example: dark blue background for balls section
    glClearColor(ballsBgColor.x, ballsBgColor.y, ballsBgColor.z, ballsBgColor.w);
    glClear(GL_COLOR_BUFFER_BIT);

    // Disable the scissor test to not affect subsequent rendering
    glDisable(GL_SCISSOR_TEST);

    // Set the viewport for rendering the balls (if different from scissor box)
    glViewport(ballsViewportX, ballsViewportY, ballsViewportWidth, ballsViewportHeight);

    // Render the balls
    BallManager::drawBalls();
    BallManager::drawWalls();


    // Reset the viewport to the full window size for UI rendering
    ImGuiIO& io = ImGui::GetIO();
    glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);

    // Start the Dear ImGui frame and render UI
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGLUT_NewFrame();
    ImGui::NewFrame();
    {
        
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

        int panelWidth = 500;
        int panelHeight = 1080;

        ImGui::SetNextWindowPos(ImVec2(MAX_WIDTH - panelWidth, 0)); // Position the window at the top-left corner
        ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight));
        ImGui::Begin("Control Panel");


        ImGui::Text("Spawn Ball");
        ImGui::InputFloat("x", &ballX);
        ImGui::InputFloat("y", &ballY);
        ImGui::InputFloat("Angle", &ballAngle);
        ImGui::InputFloat("Velocity", &ballVelocity);
        if (ImGui::Button("Spawn Ball"))
        {
            for (int i = 0; i < 100; i++) {
                BallManager::addBall(Ball(ballX, ballY, ballVelocity + i / 2, ballAngle + i / 2));
            }
            
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // Spawn Wall
        ImGui::Text("Spawn Wall");
        ImGui::InputFloat("x1", &wallX1);
        ImGui::InputFloat("y1", &wallY1);
        ImGui::InputFloat("x2", &wallX2);
        ImGui::InputFloat("y2", &wallY2);
        if (ImGui::Button("Spawn Wall"))
        {
            BallManager::addWall(Wall(wallX1, wallY1, wallX2, wallY2));

        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        ImGui::Text("Number of balls: %d", BallManager::getBalls().size());

        
    }

    ImGui::End();

    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glutSwapBuffers();
}



void update(int value) {
    static int lastTime = glutGet(GLUT_ELAPSED_TIME);
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (currentTime - lastTime) / 1000.0f; // convert milliseconds to seconds
    lastTime = currentTime;


    accumulator += deltaTime;

    while (accumulator >= targetFrameTime) {
        BallManager::updateBalls(deltaTime); // Update all balls with the time elapsed
        accumulator -= targetFrameTime;

    }



    glutPostRedisplay();
    glutTimerFunc(1, update, 0);
    //BallManager::updateBalls(); // Update all balls

    //glutPostRedisplay();
    //glutTimerFunc(16, update, 0); // Schedule the next update
}


int main(int argc, char** argv) {

    glutInit(&argc, argv);
#ifdef __FREEGLUT_EXT_H__
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
#endif
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
    glutCreateWindow("Bouncing balls");

    // Setup GLUT display function
    // We will also call ImGui_ImplGLUT_InstallFuncs() to get all the other functions installed for us,
    // otherwise it is possible to install our own functions and call the imgui_impl_glut.h functions ourselves.
    glutDisplayFunc(display);
    glutTimerFunc(1, update, 0);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGLUT_Init();
    ImGui_ImplOpenGL3_Init();

    // Install GLUT handlers (glutReshapeFunc(), glutMotionFunc(), glutPassiveMotionFunc(), glutMouseFunc(), glutKeyboardFunc() etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    ImGui_ImplGLUT_InstallFuncs();
 
    // Main loop
    glutMainLoop();

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
