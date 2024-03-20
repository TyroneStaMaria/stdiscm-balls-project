#include "SpriteManager.h"
#include "Sprite.h"

using namespace std;


vector<Sprite> SpriteManager::sprites;

SpriteManager::SpriteManager() : explorerMode(false), pixelWidth(50.f), pixelHeight(50.f) {
    // Initialize mainSprite if needed, depending on how Sprite is defined
}

void SpriteManager::addSprites(const Sprite& sprite) {
    sprites.push_back(sprite);
}

void SpriteManager::drawSprites(float cameraX, float cameraY, bool isExplorerMode) {
    if (isExplorerMode && !sprites.empty()) {
        // Assuming mainSprite is the sprite you control
        Sprite& mainSprite = sprites.front();

        const float peripheryTileSize = 10.0f; // Tile size in pixels
        const int peripheryWidthTiles = 33; // Number of horizontal tiles
        const int peripheryHeightTiles = 19; // Number of vertical tiles
        const float peripheryWidth = peripheryWidthTiles * peripheryTileSize;
        const float peripheryHeight = peripheryHeightTiles * peripheryTileSize;

        // World dimensions
        const float worldWidth = 1280;
        const float worldHeight = 720;

        // Adjust camera to prevent sprite from being centered near edges
        float adjustedCameraX = mainSprite.getX() - peripheryWidth / 2.0f;
        float adjustedCameraY = mainSprite.getY() - peripheryHeight / 2.0f;

        // Prevent camera from going beyond the world bounds (left and bottom edges)
        adjustedCameraX = max(0.0f, adjustedCameraX);
        adjustedCameraY = max(0.0f, adjustedCameraY);

        // Prevent camera from going beyond the world bounds (right and top edges)
        adjustedCameraX = min(adjustedCameraX, worldWidth - peripheryWidth);
        adjustedCameraY = min(adjustedCameraY, worldHeight - peripheryHeight);

        // Set up camera view based on adjusted positions
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(adjustedCameraX, adjustedCameraX + peripheryWidth, adjustedCameraY, adjustedCameraY + peripheryHeight);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Draw the sprite at its world position relative to the adjusted camera
        float spriteDrawX = mainSprite.getX() - adjustedCameraX;
        float spriteDrawY = mainSprite.getY() - adjustedCameraY;
        mainSprite.draw(spriteDrawX, spriteDrawY);
    }
    else {
        // Standard drawing code for non-explorer mode
        for (auto& sprite : sprites) {
            sprite.draw(cameraX, cameraY);
        }
    }
}

vector<Sprite>& SpriteManager::getSprites() {
    return sprites;
}