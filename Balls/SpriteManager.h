#pragma once
#include "Sprite.h"
#include <vector>

using namespace std;

class SpriteManager {
public:
    SpriteManager(); 
    static void addSprites(const Sprite& sprite);
    void drawSprites(float cameraX, float cameraY, bool isExplorerMode);
    static vector<Sprite>& getSprites();

    bool explorerMode;
    Sprite mainSprite;
    float pixelWidth;
    float pixelHeight;

private:
    static vector<Sprite> sprites;
};

