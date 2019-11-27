#include "UI_Navigation.h"
#include "MapGenerator.h"


UI_Navigation::UI_Navigation(const float _scale, AssetLoader &assetLoader) : scale(_scale)
{
    // Move some of this code to assetloader

    screenWidth = assetLoader.backgroundDay.getGlobalBounds().width;
    screenHeight = assetLoader.backgroundDay.getGlobalBounds().height;
    playButtonLoc = sf::Vector2f(screenWidth/4.0f-assetLoader.playButton.getGlobalBounds().width/2.0f, screenHeight-assetLoader.ground.getGlobalBounds().height-assetLoader.playButton.getGlobalBounds().height);
    scoreButtonLoc = sf::Vector2f(screenWidth/4.0f*3-assetLoader.scoreButton.getGlobalBounds().width/2.0f, screenHeight-assetLoader.ground.getGlobalBounds().height-assetLoader.scoreButton.getGlobalBounds().height);


    assetLoader.playButton.setPosition(playButtonLoc);
    assetLoader.scoreButton.setPosition(scoreButtonLoc);
    assetLoader.titleText.setPosition(screenWidth/2.0f-assetLoader.titleText.getGlobalBounds().width/2.0f, screenHeight/3.0f-assetLoader.titleText.getGlobalBounds().height/2.0f);

    // This should be exactly centered
    assetLoader.beginScreen.setPosition(screenWidth/2-assetLoader.beginScreen.getGlobalBounds().width/2, screenHeight/2-assetLoader.beginScreen.getGlobalBounds().height/2);

    assetLoader.beginText.setPosition(screenWidth/2-assetLoader.beginText.getGlobalBounds().width/2, screenHeight/3-assetLoader.beginText.getGlobalBounds().height);
    assetLoader.gameoverText.setPosition(screenWidth/2-assetLoader.gameoverText.getGlobalBounds().width/2, screenHeight/3-assetLoader.gameoverText.getGlobalBounds().height);

}

void UI_Navigation::DrawUI(sf::RenderWindow &window, float deltaTime, AssetLoader &assetLoader, MapGenerator& mapGenerator)
{
    // Calculate score
    const int rawGamescore = (mapGenerator.distance+assetLoader.bird[0].getPosition().x+mapGenerator.pipeDistance)/mapGenerator.pipeDistance;
    gameScore = (rawGamescore < 0)? 0 : rawGamescore;

    // Draw FPS, calculating it without epsilon apparently hides the titletext
    DrawNumber(window, assetLoader, FontType::SmallNum, Alignment::Center, {26*scale, 14*scale}, static_cast<long>(1/(deltaTime+0.000000001f)));

    switch (uiState)
    {
    case MainMenu:
        window.draw(assetLoader.playButton);
        window.draw(assetLoader.scoreButton);
        window.draw(assetLoader.titleText);

        break;
    case PreGame:
        window.draw(assetLoader.beginScreen);
        window.draw(assetLoader.beginText);
        DrawNumber(window, assetLoader, FontType::LargeNum, Alignment::Center, {screenWidth/2, screenWidth/4}, gameScore);
        break;
    case InGame:
        DrawNumber(window, assetLoader, FontType::LargeNum, Alignment::Center, {screenWidth/2, screenWidth/4}, gameScore);
        break;
    case GameOver:
        window.draw(assetLoader.scoreBoard);
        window.draw(assetLoader.playButton);
        window.draw(assetLoader.scoreButton);
        window.draw(assetLoader.gameoverText);
        DrawNumber(window, assetLoader, FontType::MediumNum, Alignment::Right, {screenWidth*0.815f, screenHeight*0.455f}, gameScore);
        DrawNumber(window, assetLoader, FontType::MediumNum, Alignment::Right, {screenWidth*0.815f, screenHeight*0.537f}, highScore);

        break;

    }

}

void UI_Navigation::HandleEvent(sf::RenderWindow &window, sf::Event event, AssetLoader& assetLoader)
{
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

    switch (uiState)
    {
    case MainMenu:
        if(assetLoader.playButton.getGlobalBounds().contains(mousePos) && event.type == sf::Event::MouseButtonReleased)
        {
            ChangeState(UI_State::PreGame);
        }
        break;
    case PreGame:
        if(event.type == event.KeyPressed)
        {
            ChangeState(UI_State::InGame);
        }
        break;
    case InGame:

        break;
    case GameOver:
        if(assetLoader.playButton.getGlobalBounds().contains(mousePos) && event.type == sf::Event::MouseButtonReleased)
        {
            ChangeState(UI_State::PreGame);
        }
        break;

    }
}

void UI_Navigation::HandleNewState(sf::RenderWindow &window, AssetLoader &assetLoader, UI_State newState)
{
    if(newState == UI_State::GameOver)
    {
        if(gameScore > highScore)
        {
            highScore = gameScore;
            newHighscore = true;
        }
    }
    if(newState == UI_State::PreGame)
    {
        newHighscore = false;
    }
}

void UI_Navigation::ChangeState(UI_State newState)
{
    uiState = newState;
    stateChanged = true;
}

bool UI_Navigation::StateChanged()
{
    if(stateChanged)
    {
        stateChanged = false;
        return true;
    }
    else
    {
        return false;
    }
}


void UI_Navigation::DrawNumber(sf::RenderWindow &window, AssetLoader& assetLoader, FontType fontType, Alignment alignment, sf::Vector2f position, long number)
{
    std::string digits = std::to_string(number);
    float distanceBetweenNumbers = 4;
    auto* numberSprites = &assetLoader.smallNumbers;

    switch (fontType) {
    case SmallNum:
        numberSprites = &assetLoader.smallNumbers;
        distanceBetweenNumbers = 4;
        break;
    case MediumNum:
        numberSprites = &assetLoader.mediumNumbers;
        distanceBetweenNumbers = 4;
        break;
    case LargeNum:
        numberSprites = &assetLoader.largeNumbers;
        distanceBetweenNumbers = 4;
        break;

    }

    // Calculate string width (Kinda inefficient)
    float stringWidth = 0.f;
    for(int i = 0; i < digits.length(); i++)
    {
        const int letterIndex = digits[i]-'0';
        // Only move top right corner
        const int letterWidth = (*numberSprites)[letterIndex].getGlobalBounds().width;
        stringWidth += letterWidth+distanceBetweenNumbers;
    }

    float currentStringLength = 0;

    for(int i = 0; i < digits.length(); i++)
    {
        const int letterIndex = digits[i]-'0';
        const int letterWidth = (*numberSprites)[letterIndex].getGlobalBounds().width;

        (*numberSprites)[letterIndex].setPosition(position);

        (*numberSprites)[letterIndex].move(currentStringLength, 0);

        if(alignment == Alignment::Center)
        {
            (*numberSprites)[letterIndex].move(-stringWidth/2.0f, 0);
        }
        else if(alignment == Alignment::Right)
        {
            (*numberSprites)[letterIndex].move(-stringWidth, 0);
        }

        currentStringLength += distanceBetweenNumbers+letterWidth;

        window.draw((*numberSprites)[letterIndex]);
    }
}


