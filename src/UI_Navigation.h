#ifndef UI_NAVIGATION_H
#define UI_NAVIGATION_H

#include <string>
#include <sstream>
#include <iostream>

#include <SFML/Graphics.hpp>
#include "AssetLoader.h"

enum UI_State { MainMenu, PreGame, InGame, GameOver};
enum FontType { SmallNum, MediumNum, LargeNum};


class UI_Navigation
{
public:
    UI_Navigation(const float _scale, AssetLoader& assetLoader);

    void DrawUI(sf::RenderWindow &window, float deltaTime, AssetLoader& assetLoader);
    void HandleEvent(sf::RenderWindow &window, sf::Event event, AssetLoader& assetLoader);

    void DrawNumber(sf::RenderWindow &window, AssetLoader& assetLoader,FontType fontType, sf::Vector2f position, uint number);


    float screenWidth;
    float screenHeight;

    sf::Vector2f playButtonLoc;
    sf::Vector2f scoreButtonLoc;


    UI_State uiState = UI_State::MainMenu;
    const float scale;
    int gameScore = 1264;
};

#endif // UI_NAVIGATION_H