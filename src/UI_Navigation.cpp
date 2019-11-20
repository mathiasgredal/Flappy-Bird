#include "UI_Navigation.h"


UI_Navigation::UI_Navigation(const float _scale, AssetLoader &assetLoader) : scale(_scale)
{
    screenWidth = assetLoader.backgroundDay.getGlobalBounds().width;
    screenHeight = assetLoader.backgroundDay.getGlobalBounds().height;
    playButtonLoc = sf::Vector2f(screenWidth/4.0f-assetLoader.playButton.getGlobalBounds().width/2.0f, screenHeight-assetLoader.ground.getGlobalBounds().height-assetLoader.playButton.getGlobalBounds().height);
    scoreButtonLoc = sf::Vector2f(screenWidth/4.0f*3-assetLoader.scoreButton.getGlobalBounds().width/2.0f, screenHeight-assetLoader.ground.getGlobalBounds().height-assetLoader.scoreButton.getGlobalBounds().height);


    assetLoader.playButton.setPosition(playButtonLoc);
    assetLoader.scoreButton.setPosition(scoreButtonLoc);
    assetLoader.titleText.setPosition(screenWidth/2.0f-assetLoader.titleText.getGlobalBounds().width/2.0f, screenHeight/3.0f-assetLoader.titleText.getGlobalBounds().height/2.0f);
}

void UI_Navigation::DrawUI(sf::RenderWindow &window, float deltaTime, AssetLoader &assetLoader)
{
    switch (uiState)
    {
    case MainMenu:
        window.draw(assetLoader.playButton);
        window.draw(assetLoader.scoreButton);
        window.draw(assetLoader.titleText);
        break;
    case PreGame:
        break;
    case InGame:
        DrawNumber(window, assetLoader, FontType::SmallNum, {screenWidth/2, screenWidth/4}, gameScore);
        break;
    case GameOver:
        break;

    }

}

void UI_Navigation::HandleEvent(sf::RenderWindow &window, sf::Event event, AssetLoader& assetLoader)
{
    sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);

    switch (uiState)
    {
    case MainMenu:
        if(assetLoader.playButton.getGlobalBounds().contains(mousePos) && event.type == sf::Event::MouseButtonReleased)
        {
            uiState = UI_State::InGame;
        }
        break;
    case PreGame:
        break;
    case InGame:

        break;
    case GameOver:
        break;

    }
}

void UI_Navigation::DrawNumber(sf::RenderWindow &window, AssetLoader& assetLoader, FontType fontType, sf::Vector2f position, uint number)
{
    std::string digits = std::to_string(number);
    const float distanceBetweenNumbers = 40;
    auto& numberSprites = assetLoader.smallNumbers;
    switch (fontType) {
    case SmallNum:
        numberSprites = assetLoader.smallNumbers;
        break;
    case MediumNum:
        numberSprites = assetLoader.mediumNumbers;
        break;
    case LargeNum:
        numberSprites = assetLoader.largeNumbers;
        break;

    }

    // Calculate string width (Kinda inefficient)
    float stringWidth = 0.f;
    for(int i = 0; i < digits.length(); i++)
    {
        const int letterIndex = digits[i]-'0';
        // Only move top right corner
        const int letterWidth = numberSprites[letterIndex].getGlobalBounds().width;
        stringWidth += letterWidth+distanceBetweenNumbers;
    }

    for(int i = 0; i < digits.length(); i++)
    {

        const int letterIndex = digits[i]-'0';
        // Only move top right corner
        const int letterWidth = numberSprites[letterIndex].getGlobalBounds().width;


        numberSprites[letterIndex].setPosition(position);

        numberSprites[letterIndex].move(distanceBetweenNumbers*i-letterWidth, 0);
        numberSprites[letterIndex].move(-stringWidth/4.0f, 0);

        window.draw(numberSprites[letterIndex]);
    }


}


