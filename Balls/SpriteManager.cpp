#include "SpriteManager.h"
#include "Sprite.h"

using namespace std;

vector<Sprite> SpriteManager::sprites;

SpriteManager::SpriteManager() : explorerMode(false), pixelWidth(50.f), pixelHeight(50.f) {
}

void SpriteManager::addSprites(const Sprite& sprite) {
    sprites.push_back(sprite);
}

void SpriteManager::drawSprites(float cameraX, float cameraY, bool isExplorerMode) {
    if (isExplorerMode) {
        mainSprite = sprites.front(); 

        const float peripheryTileSize = 10.0f; // Tile size in pixels
        const int peripheryWidthTiles = 33; // Number of horizontal tiles
        const int peripheryHeightTiles = 19; // Number of vertical tiles
        const float peripheryWidth = peripheryWidthTiles * peripheryTileSize;
        const float peripheryHeight = peripheryHeightTiles * peripheryTileSize;

        // Center camera on sprite
        cameraX = mainSprite.getX() - peripheryWidth / 2.0f;
        cameraY = mainSprite.getY() - peripheryHeight / 2.0f;

        // Set up camera view
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(cameraX, cameraX + peripheryWidth, cameraY, cameraY + peripheryHeight);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        mainSprite.draw(0, 0);
    }
    else {
        for (auto& sprite : sprites) {
            sprite.draw(cameraX, cameraY);
        }
    }
}

vector<Sprite>& SpriteManager::getSprites() {
    return sprites;
}