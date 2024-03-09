#include <GL/glut.h> // Include the GLUT header file
#include <iostream>
#include <numbers>
#include <random>
#include <typeinfo>

#include "imgui.h"

#include "imgui_impl_opengl3.h"

#include "imgui_impl_glut.h"
#include "Ball.h"
#include "BallManager.h"
#include "Point.h"
#include "SpriteManager.h"
#include "Sprite.h"

using namespace std;

static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

const int MAX_WIDTH = 1920;
const int MAX_HEIGHT = 1080;
const int MAX_BATCH = 100;

int n = 0;

int batch = 0;
int ballsSpawned = 0;
int currBatch = 0;

Point startBall = {0, 0};
Point endBall = {0, 0};

pair<float, float> angle;
pair<float, float> velocity;

Point wallPoint1 = {0, 0};
Point wallPoint2 = {0, 0};

const int targetFPS = 60;
const float targetFrameTime = 1.0f / targetFPS;
float accumulator = 0.0f;
static int currentForm = 0;

bool spawning = false;

int frameCount = 0;
float lastFrameRateCalculationTime = 0.0f;
float calculatedFrameRate = 0.0f;

float backgroundOffsetX = 0.0f;
float backgroundOffsetY = 0.0f;

float cameraX = 0.0f;
float cameraY = 0.0f;

bool isExplorerMode = false;
const float tileSize = 1000.0f; // Example tile size, adjust based on your game's scale


void toggleExplorerMode() {
    isExplorerMode = !isExplorerMode;
}

// Function to adjust camera movement based on keyboard input
void keyboard(unsigned char key, int x, int y) {
    float cameraSpeed = 5.0f;
    
    if (isExplorerMode && !SpriteManager::getSprites().empty()) {
        Sprite& currentSprite = SpriteManager::getSprites().front(); // Assuming the controlled sprite is the first one
        switch (key) {
        case 'w': currentSprite.moveUp(cameraSpeed); break;
        case 's': currentSprite.moveDown(cameraSpeed); break;
        case 'a': currentSprite.moveLeft(cameraSpeed); break;
        case 'd': currentSprite.moveRight(cameraSpeed); break;
        }
    }
    else {
        switch (key) {
            case 'w':
                cameraY -= cameraSpeed;
                break;
            case 's':
                cameraY += cameraSpeed;
                break;
            case 'a':
                cameraX += cameraSpeed;
                break;
            case 'd':
                cameraX -= cameraSpeed;
                break;
        }
    }
    glutPostRedisplay();
}

static void sliderFloat(string label, float *var, float maxValue, float minValue = 0.0f)
{

    ImGui::Text("%s", label.c_str());
    ImGui::Separator();

    ImGui::SetNextItemWidth(150.0f);

    string inputId = "##input" + label;
    string sliderId = "##slider" + label;

    ImGui::InputFloat(inputId.c_str(), var, 0.0f, 0.0f, "%.2f");
    ImGui::SameLine();

    ImGui::SetNextItemWidth(400.0f);
    ImGui::SliderFloat(sliderId.c_str(), var, minValue, maxValue, " ");

    *var = clamp(*var, minValue, maxValue);

    ImGui::Spacing();
}

static void sliderInt(string label, int *var, int maxValue)
{
    ImGui::Text("%s", label.c_str());
    ImGui::Separator();

    ImGui::SetNextItemWidth(150.0f);

    string inputId = "##input" + label;
    string sliderId = "##slider" + label;

    ImGui::InputInt(inputId.c_str(), var, 0.0f, 0.0f);
    ImGui::SameLine();

    ImGui::SetNextItemWidth(400.0f);
    ImGui::SliderInt(sliderId.c_str(), var, 0.0f, maxValue, " ");

    *var = clamp(*var, 0, maxValue);

    ImGui::Spacing();
}

void display()
{
    // First, clear the entire window with the main background color
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    // Define the viewport and scissor box for the balls section
    GLint ballsViewportX = 0 - static_cast<int>(backgroundOffsetX);
    GLint ballsViewportY = 220 - static_cast<int>(backgroundOffsetY);
    GLsizei ballsViewportWidth = 1280;
    GLsizei ballsViewportHeight = 720;

    glEnable(GL_SCISSOR_TEST);
    glScissor(ballsViewportX, ballsViewportY, ballsViewportWidth, ballsViewportHeight);
    glViewport(ballsViewportX, ballsViewportY, ballsViewportWidth, ballsViewportHeight);

    ImVec4 ballsBgColor = ImVec4(0.2f, 0.3f, 0.4f, 1.0f);
    glClearColor(ballsBgColor.x, ballsBgColor.y, ballsBgColor.z, ballsBgColor.w);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, ballsViewportWidth, 0, ballsViewportHeight); // Set coordinate system with (0,0) at bottom left

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    BallManager::drawBalls();
    BallManager::drawWalls();
    SpriteManager::drawSprites(cameraX, cameraY);

    // Disable the scissor test to not affect subsequent rendering
    glDisable(GL_SCISSOR_TEST);

    // Reset the viewport to the full window size for UI rendering
    ImGuiIO &io = ImGui::GetIO();
    glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);

    // Start the Dear ImGui frame and render UI
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGLUT_NewFrame();
    ImGui::NewFrame();
    {
        float oldSize = ImGui::GetFont()->Scale;
        ImGui::GetFont()->Scale *= 1.25;
        ImGui::PushFont(ImGui::GetFont());

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

        int panelWidth = 600;
        int panelHeight = 1080;

        ImGui::SetNextWindowPos(ImVec2(MAX_WIDTH - panelWidth, 0)); // Position the window at the top-left corner
        ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight));
        ImGui::Begin("Control Panel");

        const char *options[] = {"0", "1", "2", "3"};

        for (int i = 0; i < IM_ARRAYSIZE(options); i++)
        {

            if (spawning)
            {
                ImGui::BeginDisabled();
                ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
                ImGui::RadioButton(options[i], &currentForm, i);
                ImGui::PopStyleVar();
                ImGui::EndDisabled();
            }
            else
            {
                if (ImGui::RadioButton(options[i], &currentForm, i))
                {
                    n = 0;

                    startBall = {0, 0};
                    endBall = {0, 0};

                    angle = {0, 0};
                    velocity = {0, 0};
                }
            }

            if (i < IM_ARRAYSIZE(options) - 1)
            {
                ImGui::SameLine();
            }
        }

        ImGui::Text("Spawn Ball");

        switch (currentForm)
        {
        case 0:
            sliderFloat("x", &startBall.x, ballsViewportWidth);
            sliderFloat("y", &startBall.y, ballsViewportHeight);
            sliderFloat("angle", &angle.first, 360.0f);
            sliderFloat("velocity", &velocity.first, 2000.0f, 300.0f);
            if (ImGui::Button("Spawn Ball"))
            {
                BallManager::addBall(Ball(startBall.x, startBall.y, velocity.first, angle.first));
            }
            break;
        case 1:
            sliderInt("n", &n, 10000);

            sliderFloat("start x", &startBall.x, ballsViewportWidth);
            sliderFloat("start y", &startBall.y, ballsViewportHeight);
            sliderFloat("end x", &endBall.x, ballsViewportWidth);
            sliderFloat("end y", &endBall.y, ballsViewportHeight);
            sliderFloat("angle", &angle.first, 360.0f);
            sliderFloat("velocity", &velocity.first, 2000.0f, 300.0f);
            // spawning = ImGui::Button("Spawn Ball");
            if (ImGui::Button("Spawn Ball") && !spawning)
            {
                spawning = true;
                ballsSpawned = 0;
                // BallManager::addBallsDistance(n, startBall, endBall, velocity.first, angle.first);
            }
            break;
        case 2:
            sliderInt("n", &n, 10000);

            sliderFloat("x", &startBall.x, ballsViewportWidth);
            sliderFloat("y", &startBall.y, ballsViewportHeight);
            sliderFloat("start angle", &angle.first, 360.0f);
            sliderFloat("end angle", &angle.second, 360.0f);
            sliderFloat("velocity", &velocity.first, 2000.0f, 300.0f);
            // spawning = ImGui::Button("Spawn Ball");

            if (ImGui::Button("Spawn Ball"))
            {
                spawning = true;
                ballsSpawned = 0;
                // BallManager::addBallsAngle(n, startBall, velocity.first, angle.first, angle.second);
            }
            break;
        case 3:
            sliderInt("n", &n, 10000);

            sliderFloat("x", &startBall.x, ballsViewportWidth);
            sliderFloat("y", &startBall.y, ballsViewportHeight);
            sliderFloat("angle", &angle.first, 360.0f);
            sliderFloat("start velocity", &velocity.first, 2000.0f);
            sliderFloat("end velocity", &velocity.second, 2000.0f, 300.0f);
            // spawning = ImGui::Button("Spawn Ball");

            if (ImGui::Button("Spawn Ball"))
            {
                spawning = true;
                ballsSpawned = 0;
                // BallManager::addBallsVelocity(n, startBall, velocity.first, velocity.second, angle.first);
            }
            break;
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Controls");
        if (ImGui::Button("Explorer Mode")) {
            isExplorerMode = !isExplorerMode; // Toggle the explorer mode state
        }

        auto sprites = SpriteManager::getSprites();
        if (!sprites.empty() && isExplorerMode) {
            const auto& sprite = sprites.front();

            // Calculate new camera positions based on the sprite's position
            // The goal is to keep the sprite centered, so we adjust the camera instead of moving the sprite
            cameraX = sprite.x - MAX_WIDTH / 2;
            cameraY = sprite.y - MAX_HEIGHT / 2;
        }

        // Setup the camera or view transformation
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        if (isExplorerMode) {
            // Apply a zoom factor if needed or just center on the sprite
            gluOrtho2D(-MAX_WIDTH / 2 + cameraX, MAX_WIDTH / 2 + cameraX, -MAX_HEIGHT / 2 + cameraY, MAX_HEIGHT / 2 + cameraY);
        }
        else {
            gluOrtho2D(0, MAX_WIDTH, 0, MAX_HEIGHT);
        }
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / calculatedFrameRate, calculatedFrameRate);
        ImGui::Text("Number of balls: %zu", BallManager::getBalls().size());
        ImGui::GetFont()->Scale = oldSize;
        ImGui::PopFont();
    }

    ImGui::End();

    // Render ImGui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glutSwapBuffers();
}

void update(int value)
{
    static int lastTime = glutGet(GLUT_ELAPSED_TIME);
    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (currentTime - lastTime) / 1000.0f; // convert milliseconds to seconds
    lastTime = currentTime;

    accumulator += deltaTime;

    if (spawning && ballsSpawned == n)
    {
        spawning = false;
        ballsSpawned = 0;
        currBatch = 0;
    }

    if (spawning && ballsSpawned < n)
    {
        int toSpawn = std::min(n - ballsSpawned, MAX_BATCH);
        currBatch += toSpawn;
        switch (currentForm)
        {
        case 1:
            BallManager::addBallsDistance(n, startBall, endBall, velocity.first, angle.first, ballsSpawned, currBatch);
            break;
        case 2:

            BallManager::addBallsAngle(n, startBall, velocity.first, angle.first, angle.second, ballsSpawned, currBatch);
            break;
        case 3:

            BallManager::addBallsVelocity(n, startBall, velocity.first, velocity.second, angle.first, ballsSpawned, currBatch);
            break;
        }
        ballsSpawned += toSpawn;
    }

    // Frame rate calculation
    frameCount++;
    float timeSinceLastCalculation = currentTime / 1000.0f - lastFrameRateCalculationTime; // Also in seconds
    if (timeSinceLastCalculation >= 0.5f)
    { // Every 0.5 seconds
        calculatedFrameRate = frameCount / timeSinceLastCalculation;
        frameCount = 0;
        lastFrameRateCalculationTime = currentTime / 1000.0f;
    }

    while (accumulator >= targetFrameTime)
    {
        BallManager::updateBalls(deltaTime); // Update all balls with the time elapsed
        accumulator -= targetFrameTime;
    }

    glutPostRedisplay();
    glutTimerFunc(1, update, 0);
}

int main(int argc, char **argv)
{


    glutInit(&argc, argv);
#ifdef __FREEGLUT_EXT_H__
    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
#endif
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);
    glutInitWindowSize(MAX_WIDTH, MAX_HEIGHT);
    glutCreateWindow("Bouncing balls");

    glutDisplayFunc(display);
    glutTimerFunc(1, update, 0);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImGui_ImplGLUT_InstallFuncs();
    // io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGLUT_Init();

#ifdef GL_VERSION_2_0
    ImGui_ImplOpenGL3_Init("#version 120");
#else
    ImGui_ImplOpenGL3_Init();
#endif

    ImGui_ImplGLUT_InstallFuncs();

    SpriteManager::addSprites(Sprite(20, 20));
 
    glutKeyboardFunc(keyboard);

    // Main loop
    glutMainLoop();

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
