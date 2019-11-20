#ifndef PLAYER_H
#define PLAYER_H

#include "AssetLoader.h"
#include "UI_Navigation.h"

class Player
{
public:
    Player(const float _scale, AssetLoader& assetLoader);

    void DrawPlayer(sf::RenderWindow &window, AssetLoader& assetLoader, UI_State uiState);
    void AnimatePlayer(float deltaTime, AssetLoader& assetLoader);
    void UpdatePlayer(float deltaTime, AssetLoader& assetLoader);
    void Jump();

    const float scale;

    // Animation
    const float animationSpeed = 0.2f;
    float timeSinceLastUpdate = 0;
    int animationFrame = 0;

    // Physics
    const float gravity = 2000.0f;
    const float terminalVelocity = -1300;
    const float jumpheight = 35.0f;
    const float jumpvelocity = 800.0f;
    float birdHeight = 0;
    float velocity = 0;

    // Weird bird rotation (NOT IMPLEMENTED YET)
    const float topRotation = -30;
    const float bottomRotation = 90;

};


#endif // PLAYER_H
