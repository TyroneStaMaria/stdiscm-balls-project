#include <GL/glut.h> // Include the GLUT header file
#include <iostream>
#include <numbers>
#include <random>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glut.h"
#include "Ball.h"
#include "BallManager.h"
#include "Point.h"

using namespace std;

static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

const int MAX_WIDTH = 1920;
const int MAX_HEIGHT = 1080;

int n = 0;

Point startBall = {0, 0};
Point endBall = { 0, 0 };

pair<float, float> angle;
pair<float, float> velocity;

Point wallPoint1 = { 0, 0 };
Point wallPoint2 = { 0, 0 };

const int targetFPS = 60;
const float targetFrameTime = 1.0f / targetFPS;
float accumulator = 0.0f;


void display() {
    // First, clear the entire window with the main background color
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    // Define the viewport and scissor box for the balls section
    GLint ballsViewportX = 0; // Starting X position
    GLint ballsViewportY = 360; // Starting Y position
    GLsizei ballsViewportWidth = 1280; // Width of the section
    GLsizei ballsViewportHeight = 720; // Height of the section

    // Enable scissor test and set the scissor box
    glEnable(GL_SCISSOR_TEST);
    glScissor(ballsViewportX, ballsViewportY, ballsViewportWidth, ballsViewportHeight);
    glViewport(ballsViewportX, ballsViewportY, ballsViewportWidth, ballsViewportHeight);

    // Clear the balls section with a different background color
    ImVec4 ballsBgColor = ImVec4(0.2f, 0.3f, 0.4f, 1.0f); // Example: dark blue background for balls section
    glClearColor(ballsBgColor.x, ballsBgColor.y, ballsBgColor.z, ballsBgColor.w);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, ballsViewportWidth, 0, ballsViewportHeight); // Set coordinate system with (0,0) at bottom left

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    BallManager::drawBalls();
    BallManager::drawWalls();

    // Disable the scissor test to not affect subsequent rendering
    glDisable(GL_SCISSOR_TEST);

    // Set the viewport for rendering the balls (if different from scissor box)

    // Render the balls
    


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

        static int currentForm = 0;

        ImGui::RadioButton("0", &currentForm, 0); ImGui::SameLine();
        ImGui::RadioButton("1", &currentForm, 1); ImGui::SameLine();
        ImGui::RadioButton("2", &currentForm, 2); ImGui::SameLine();
        ImGui::RadioButton("3", &currentForm, 3); 

        ImGui::Text("Spawn Ball");
        
        switch (currentForm) {
            case 0:
                ImGui::InputFloat("x", &startBall.x);
                ImGui::InputFloat("y", &startBall.y);
                ImGui::InputFloat("angle", &angle.first);
                ImGui::InputFloat("velocity", &velocity.first);
                if (ImGui::Button("Spawn Ball"))
                {
                    BallManager::addBall(Ball(startBall.x, startBall.y, velocity.first, angle.first));
                }
                break;
            case 1:
                ImGui::InputInt("n", &n);
                ImGui::InputFloat("start x", &startBall.x);
                ImGui::InputFloat("start y", &startBall.y);
                ImGui::InputFloat("end x", &endBall.x);
                ImGui::InputFloat("end y", &endBall.y);
                ImGui::InputFloat("angle", &angle.first);
                ImGui::InputFloat("velocity", &velocity.first);
                if (ImGui::Button("Spawn Ball"))
                {
                    BallManager::addBallsDistance(n, startBall, endBall, velocity.first, angle.first);
                }
                break;
            case 2:
                ImGui::InputInt("n", &n);
                ImGui::InputFloat("x", &startBall.x);
                ImGui::InputFloat("y", &startBall.y);
                ImGui::InputFloat("start angle", &angle.first);
                ImGui::InputFloat("end angle", &angle.second);
                ImGui::InputFloat("velocity", &velocity.first);
                if (ImGui::Button("Spawn Ball"))
                {
                    BallManager::addBallsAngle(n, startBall, velocity.first, angle.first, angle.second);
                }
                break;
            case 3:
                ImGui::InputInt("n", &n);
                ImGui::InputFloat("x", &startBall.x);
                ImGui::InputFloat("y", &startBall.y);
                ImGui::InputFloat("angle", &angle.first);
                ImGui::InputFloat("start velocity", &velocity.first);
                ImGui::InputFloat("end velocity", &velocity.second);
                if (ImGui::Button("Spawn Ball"))
                {
                    BallManager::addBallsVelocity(n, startBall, velocity.first, velocity.second, angle.first);
                }
                break;
        }


        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // Spawn Wall
        ImGui::Text("Spawn Wall");
        ImGui::InputFloat("x1", &wallPoint1.x);
        ImGui::InputFloat("y1", &wallPoint1.y);
        ImGui::InputFloat("x2", &wallPoint2.x);
        ImGui::InputFloat("y2", &wallPoint2.y);
        if (ImGui::Button("Spawn Wall"))
        {
            BallManager::addWall(Wall(wallPoint1, wallPoint2));

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
