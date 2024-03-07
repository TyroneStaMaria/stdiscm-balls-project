#include "SpriteManager.h"
#include "Sprite.h"

using namespace std;


vector<Sprite> SpriteManager::sprites;


void SpriteManager::addSprites(const Sprite& sprite) {
    sprites.push_back(sprite);
}

void SpriteManager::drawSprites(float cameraX, float cameraY) {
    for (auto& sprite : sprites) {
        sprite.draw(cameraX, cameraY);
    }
}

vector<Sprite> SpriteManager::getSprites() {
    return sprites;
}