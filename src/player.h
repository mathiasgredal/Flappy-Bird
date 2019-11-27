#ifndef PLAYER_H
#define PLAYER_H

#include "AssetLoader.h"
#include "UI_Navigation.h"

class Player
{
public:
    Player(const float _scale, const float _speed, AssetLoader& assetLoader);

    void HandleNewState(sf::RenderWindow &window, AssetLoader& assetLoader, UI_State newState);

    void DrawPlayer(sf::RenderWindow &window, AssetLoader& assetLoader, float deltaTime, UI_State uiState);
    void AnimatePlayer(float deltaTime, AssetLoader& assetLoader);
    void UpdatePlayer(float deltaTime, AssetLoader& assetLoader);
    void Jump();

    const float scale;
    const float speed;

    float distance = 0;

    // Animation
    const float animationSpeed = 0.2f;
    float timeSinceLastUpdate = 0;
    int animationFrame = 0;

    // Physics
    const float gravity = 4000.0f/3*scale;
    const float terminalVelocity = -330.0f*scale;
    const float jumpheight = 11.66f*scale;
    const float jumpvelocity = 350.0f*scale;
    float birdHeight = 0;
    float velocity = 0;

    // Weird bird rotation (NOT IMPLEMENTED YET)
    const float topRotation = -30;
    const float bottomRotation = 90;

};


#endif // PLAYER_H
