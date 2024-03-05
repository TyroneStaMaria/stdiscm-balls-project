#include "SpriteManager.h"
#include "Sprite.h"

using namespace std;


vector<Sprite> SpriteManager::sprites;


void SpriteManager::addSprites(const Sprite& sprite) {
    sprites.push_back(sprite);
}

void SpriteManager::drawSprites() {
    for (auto& sprite : sprites) {
        sprite.draw();
    }
}

vector<Sprite> SpriteManager::getSprites() {
    return sprites;
}