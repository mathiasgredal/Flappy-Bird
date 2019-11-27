#ifndef UI_NAVIGATION_H
#define UI_NAVIGATION_H

#include <string>
#include <sstream>
#include <iostream>

#include <SFML/Graphics.hpp>
#include "AssetLoader.h"

class MapGenerator;

enum UI_State { MainMenu, PreGame, InGame, GameOver};
enum FontType { SmallNum, MediumNum, LargeNum};
enum Alignment {Left, Center, Right};


class UI_Navigation
{
public:
    UI_Navigation(const float _scale, AssetLoader& assetLoader);

    void DrawUI(sf::RenderWindow &window, float deltaTime, AssetLoader& assetLoader, MapGenerator& mapGenerator);
    void HandleEvent(sf::RenderWindow &window, sf::Event event, AssetLoader& assetLoader);
    void HandleNewState(sf::RenderWindow &window, AssetLoader& assetLoader, UI_State newState);

    void ChangeState(UI_State newState);
    bool StateChanged();



    void DrawNumber(sf::RenderWindow &window, AssetLoader& assetLoader, FontType fontType, Alignment alignment, sf::Vector2f position, long number);

    float screenWidth;
    float screenHeight;

    sf::Vector2f playButtonLoc;
    sf::Vector2f scoreButtonLoc;

    bool stateChanged = false;

    UI_State uiState = UI_State::MainMenu;
    const float scale;
    unsigned long gameScore = 0;
    unsigned long highScore = 0;
    bool newHighscore = false;
};

#endif // UI_NAVIGATION_H
