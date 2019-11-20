#include "player.h"


double map2(double x, double in_min, double in_max, double out_min, double out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


Player::Player(const float _scale, AssetLoader& assetLoader) : scale(_scale)
{


}

void Player::UpdatePlayer(float deltaTime, AssetLoader &assetLoader)
{
    if(velocity < terminalVelocity)
    {
        velocity = terminalVelocity;
    }

    velocity -= gravity*deltaTime;
    birdHeight += velocity*deltaTime;

    assetLoader.bird.at(animationFrame).setPosition(assetLoader.backgroundDay.getGlobalBounds().width/2-60*scale, -birdHeight);

    //const float rotation = (velocity < -400)? map2(velocity, terminalVelocity, -400, bottomRotation, topRotation) : topRotation;



    //assetLoader.bird.at(animationFrame).setRotation(rotation);
}

void Player::DrawPlayer(sf::RenderWindow &window, AssetLoader &assetLoader, UI_State uiState)
{

    if(uiState == UI_State::MainMenu)
    {
        // Center bird
        const float centerScreenX = assetLoader.backgroundDay.getGlobalBounds().width/2.0f;
        const float centerScreenY = assetLoader.backgroundDay.getGlobalBounds().height/2.0f;
        const float centerBirdX = assetLoader.bird[animationFrame].getGlobalBounds().width/2.0f;
        const float centerBirdY = assetLoader.bird[animationFrame].getGlobalBounds().height/2.0f;

        assetLoader.bird[animationFrame].setPosition(centerScreenX-centerBirdX, centerScreenY-centerBirdY);

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
