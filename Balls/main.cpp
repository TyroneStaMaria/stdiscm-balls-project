#include <GL/glut.h> 
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
const float tileSize = 1000.0f; 
SpriteManager spriteManager = SpriteManager();
const float peripheryTileSize = 10.0f; // Tile size in pixels
const int peripheryWidthTiles = 33; // Number of horizontal tiles
const int peripheryHeightTiles = 19; // Number of vertical tiles
const float peripheryWidth = peripheryWidthTiles * peripheryTileSize;
const float peripheryHeight = peripheryHeightTiles * peripheryTileSize;

GLsizei ballsViewportWidth = 1280;
GLsizei ballsViewportHeight = 720;


void keyboard(unsigned char key, int x, int y) {
    
    if (isExplorerMode) {
        float cameraSpeed = 5.0f;

        Sprite& currentSprite = SpriteManager::getSprites().front();

        float spriteX = currentSprite.getX();
        float spriteY = currentSprite.getY();
        switch (key) {
        case 'w': 
            if(spriteY >= ballsViewportHeight){
                currentSprite.setY(ballsViewportHeight);            
                break;
            }
            currentSprite.moveUp(cameraSpeed); 
            cout << currentSprite.getX() << ", " << currentSprite.getY() << endl;
            break;
        case 's': 
            if(spriteY <= 0){
                currentSprite.setY(0);
                break;
            }
            currentSprite.moveDown(cameraSpeed); 
            break;
        case 'a': 
            if(spriteX <= 0){
                currentSprite.setX(0);
                break;
            }
            currentSprite.moveLeft(cameraSpeed); 
            break;
        case 'd': 
            if(spriteX >= ballsViewportWidth){
                currentSprite.setX(ballsViewportWidth);
                break;
            }
            currentSprite.moveRight(cameraSpeed); 
            break;
        }
        glutPostRedisplay();
    }
}

void drawBorderLines(float lineWidth, float borderWidth, int numLines) {
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(0, ballsViewportWidth, 0, ballsViewportHeight, -1.0, 1.0);

    glLineWidth(lineWidth);

    glColor3f(0.0f, 0.0f, 0.0f);

    Sprite& mainSprite = SpriteManager::getSprites().front();
    float spriteX = mainSprite.getX();
    float spriteY = mainSprite.getY();

    if (spriteY >= ballsViewportHeight - borderWidth) {
        for (int i = 0; i < numLines; i++) {
            glBegin(GL_LINES);
            glVertex2f(0.0f, ballsViewportHeight - i);
            glVertex2f(ballsViewportWidth, ballsViewportHeight - i);
            glEnd();
        }
    }

    if (spriteY <= borderWidth) {
        for (int i = 0; i < numLines; i++) {
            glBegin(GL_LINES);
            glVertex2f(0.0f, i);
            glVertex2f(ballsViewportWidth, i);
            glEnd();
        }
    }
    if (spriteX <= borderWidth) {
        for (int i = 0; i < numLines; i++) {
            glBegin(GL_LINES);
            glVertex2f(i, 0.0f);
            glVertex2f(i, ballsViewportHeight);
            glEnd();
        }
    }
    if (spriteX >= ballsViewportWidth - borderWidth) {
        for (int i = 0; i < numLines; i++) {
            glBegin(GL_LINES);
            glVertex2f(ballsViewportWidth - i, 0.0f);
            glVertex2f(ballsViewportWidth - i, ballsViewportHeight);
            glEnd();
        }
    }
    glPopMatrix();
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
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    GLint ballsViewportX = 0 - static_cast<int>(backgroundOffsetX);
    GLint ballsViewportY = 220 - static_cast<int>(backgroundOffsetY);

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

    if (isExplorerMode) {
        drawBorderLines(20.0f, 20.0f, 50);
        Sprite& mainSprite = SpriteManager::getSprites().front();
        float centerX = mainSprite.getX() - peripheryWidth / 4.0f;
        float centerY = mainSprite.getY() - peripheryHeight / 3.0f;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity(); 
        gluOrtho2D(centerX, centerX + peripheryWidth, centerY, centerY + peripheryHeight);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    BallManager::drawBalls();
    spriteManager.drawSprites(cameraX, cameraY, isExplorerMode);

    glDisable(GL_SCISSOR_TEST);

    ImGuiIO &io = ImGui::GetIO();
    glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);

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

        if (isExplorerMode) {
            ImGui::Text("Controls");
            if (ImGui::Button("Developer Mode")) {
                isExplorerMode = false; 
            }
        }
        else {
            const char* options[] = { "0", "1", "2", "3" };
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
                        startBall = { 0, 0 };
                        endBall = { 0, 0 };
                        angle = { 0, 0 };
                        velocity = { 0, 0 };
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
                if (ImGui::Button("Spawn Ball") && !spawning)
                {
                    spawning = true;
                    ballsSpawned = 0;
                }
                break;
            case 2:
                sliderInt("n", &n, 10000);
                sliderFloat("x", &startBall.x, ballsViewportWidth);
                sliderFloat("y", &startBall.y, ballsViewportHeight);
                sliderFloat("start angle", &angle.first, 360.0f);
                sliderFloat("end angle", &angle.second, 360.0f);
                sliderFloat("velocity", &velocity.first, 2000.0f, 300.0f);
                if (ImGui::Button("Spawn Ball"))
                {
                    spawning = true;
                    ballsSpawned = 0;
                }
                break;
            case 3:
                sliderInt("n", &n, 10000);
                sliderFloat("x", &startBall.x, ballsViewportWidth);
                sliderFloat("y", &startBall.y, ballsViewportHeight);
                sliderFloat("angle", &angle.first, 360.0f);
                sliderFloat("start velocity", &velocity.first, 2000.0f);
                sliderFloat("end velocity", &velocity.second, 2000.0f, 300.0f);
                if (ImGui::Button("Spawn Ball"))
                {
                    spawning = true;
                    ballsSpawned = 0;
                }
                break;
            }

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::Text("Controls");
            if (ImGui::Button("Explorer Mode")) {
                isExplorerMode = !isExplorerMode; 
            }
        }
        
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / calculatedFrameRate, calculatedFrameRate);
        ImGui::Text("Number of balls: %zu", BallManager::getBalls().size());
        ImGui::GetFont()->Scale = oldSize;
        ImGui::PopFont();

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glutSwapBuffers();
    }

}

void update(int value){
    static int lastTime = glutGet(GLUT_ELAPSED_TIME);
    static int frameCount = 0; 
    static float lastFpsTime = 0.0f; 

    int currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = (currentTime - lastTime) / 1000.0f; 
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

    while (accumulator >= targetFrameTime)
    {
        BallManager::updateBalls(deltaTime);
        accumulator -= targetFrameTime;
    }

    frameCount++;
    float fpsUpdateTime = currentTime / 1000.0f - lastFpsTime;
    if (fpsUpdateTime >= 0.5f) {
        calculatedFrameRate = frameCount / fpsUpdateTime; // Calculate FPS
        frameCount = 0;
        lastFpsTime = currentTime / 1000.0f; 
    }

    float frameProcessingTime = (glutGet(GLUT_ELAPSED_TIME) - currentTime) / 1000.0f;
    float timeUntilNextFrame = targetFrameTime - frameProcessingTime;
    int delay = max(0, static_cast<int>(timeUntilNextFrame * 1000.0f));

    glutPostRedisplay();
    glutTimerFunc(delay, update, 0); 
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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    ImGui_ImplGLUT_InstallFuncs();

    ImGui::StyleColorsDark();

    ImGui_ImplGLUT_Init();

#ifdef GL_VERSION_2_0
    ImGui_ImplOpenGL3_Init("#version 120");
#else
    ImGui_ImplOpenGL3_Init();
#endif

    ImGui_ImplGLUT_InstallFuncs();

    spriteManager.addSprites(Sprite(20, 20));
 
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();

    return 0;
}
