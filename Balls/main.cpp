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

    // Reset the viewport to the full window size for UI rendering
    ImGuiIO& io = ImGui::GetIO();
    glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);

    // Start the Dear ImGui frame and render UI
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGLUT_NewFrame();
    ImGui::NewFrame();

    ImGui::Begin("Control Panel");
    //ImGui::Text("Adjust settings and observe changes.");
    ImGui::SetCursorPos(ImVec2(100, 100));
    ImGui::PushItemWidth(200);
    static int i1 = 123;
    ImGui::InputInt("##", &i1);
    ImGui::PopItemWidth();

    ImGui::End();

    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glutSwapBuffers();
}



void update(int value) {
    BallManager::updateBalls(); // Update all balls

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // Schedule the next update
}


int main(int argc, char** argv) {

    glutInit(&argc, argv);
#ifdef __FREEGLUT_EXT_H__
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
#endif
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("Dear ImGui GLUT+OpenGL2 Example");

    // Setup GLUT display function
    // We will also call ImGui_ImplGLUT_InstallFuncs() to get all the other functions installed for us,
    // otherwise it is possible to install our own functions and call the imgui_impl_glut.h functions ourselves.
    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);

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

    for (int i = 0; i < 2; i++) {
        float randomX = distrX(eng);
        float randomY = distrY(eng);
        float randomDX = distrDX(eng);
        float randomDY = distrDY(eng);

        BallManager::addBall(Ball(randomX, randomY, randomDX, randomDY));
    }
    

    // Main loop
    glutMainLoop();

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();


    //glutInit(&argc, argv);
    //glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    //glutInitWindowSize(1280, 720);
    //glutCreateWindow("OpenGL Bouncing Ball with Class");

    

    //BallManager::addWall(Wall(-0.5f, -0.5f, -0.5f, 0.5f));


    //glutDisplayFunc(display);
    //glutTimerFunc(25, update, 0);

    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    //// Setup Dear ImGui context
    //IMGUI_CHECKVERSION();
    //ImGui::CreateContext();
    //ImGuiIO& io = ImGui::GetIO(); (void)io;

    //// Setup Platform/Renderer backends
    //ImGui_ImplGLUT_Init();
    //ImGui_ImplOpenGL3_Init("#version 460");

    //// Setup Dear ImGui style
    //ImGui::StyleColorsDark();


    //glutMainLoop();

    //ImGui_ImplOpenGL3_Shutdown();
    //ImGui_ImplGLUT_Shutdown();
    //ImGui::DestroyContext();


    return 0;
}
