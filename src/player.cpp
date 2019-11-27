#include "player.h"

constexpr double map2(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


Player::Player(const float _scale, const float _speed, AssetLoader& assetLoader) : scale(_scale), speed(_speed)
{
    birdHeight = -assetLoader.backgroundDay.getGlobalBounds().height/2;
}

void Player::HandleNewState(sf::RenderWindow &window, AssetLoader &assetLoader, UI_State newState)
{
    if(newState == UI_State::GameOver)
    {
        birdHeight = -assetLoader.backgroundDay.getGlobalBounds().height/2;
    }
}

void Player::UpdatePlayer(float deltaTime, AssetLoader &assetLoader)
{
    if(velocity < terminalVelocity)
    {
        velocity = terminalVelocity;
    }

    velocity -= gravity*deltaTime;
    birdHeight += velocity*deltaTime;



    assetLoader.bird.at(animationFrame).setPosition(assetLoader.backgroundDay.getGlobalBounds().width/4, -birdHeight);

    //const float rotation = (velocity < -400)? map2(velocity, terminalVelocity, -400, bottomRotation, topRotation) : topRotation;
    //assetLoader.bird.at(animationFrame).setRotation(rotation);
}

void Player::DrawPlayer(sf::RenderWindow &window, AssetLoader &assetLoader, float deltaTime, UI_State uiState)
{
    // Center bird
    const float centerScreenX = assetLoader.backgroundDay.getGlobalBounds().width/2.0f;
    const float centerScreenY = assetLoader.backgroundDay.getGlobalBounds().height/2.0f;
    const float centerBirdX = assetLoader.bird[animationFrame].getGlobalBounds().width/2.0f;
    const float centerBirdY = assetLoader.bird[animationFrame].getGlobalBounds().height/2.0f;

    if(uiState == UI_State::MainMenu)
    {
        AnimatePlayer(deltaTime, assetLoader);
        assetLoader.bird[animationFrame].setPosition(centerScreenX-centerBirdX, centerScreenY-centerBirdY*2);
    }

    if(uiState == UI_State::PreGame)
    {
        AnimatePlayer(deltaTime, assetLoader);
        assetLoader.bird.at(animationFrame).setPosition(assetLoader.backgroundDay.getGlobalBounds().width/4, centerScreenY-centerBirdY*2);
    }

    if(uiState == UI_State::InGame)
    {
        AnimatePlayer(deltaTime, assetLoader);
        UpdatePlayer(deltaTime, assetLoader);
    }

    window.draw(assetLoader.bird[animationFrame]);
}

void Player::AnimatePlayer(float deltaTime, AssetLoader &assetLoader)
{
    timeSinceLastUpdate += deltaTime;

    if(timeSinceLastUpdate > animationSpeed)
    {
        animationFrame++;
        timeSinceLastUpdate = 0;
    }

    if(animationFrame >= assetLoader.bird.size())
    {
        animationFrame = 0;
    }
}

void Player::Jump()
{
    birdHeight += jumpheight;
    velocity = jumpvelocity;
}
