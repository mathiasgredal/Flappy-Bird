#ifndef ASSETLOADER_H
#define ASSETLOADER_H

#include <vector>
#include <array>
#include <SFML/Graphics.hpp>

class AssetLoader
{
public:
    AssetLoader(const float scale);

    sf::Texture atlas;

    // Background
    sf::Sprite backgroundDay;
    sf::Sprite backgroundNight;
    sf::Sprite ground;

    // Game
    sf::Sprite topPipe;
    sf::Sprite bottomPipe;
    std::array<sf::Sprite, 9> bird;


    // UI Navigation

    sf::Sprite playButton;
    sf::Sprite scoreButton;

    //sf::Sprite pauseButton;
    //sf::Sprite continueButton;


    sf::Sprite scoreBoard;
    sf::Sprite medals[4]; // 0 = bronze, 1 = silver, 2 = gold, 3 = platinum


    sf::Sprite beginScreen;


    sf::Sprite titleText;
    sf::Sprite beginText;
    sf::Sprite gameoverText;


    std::array<sf::Sprite, 10> smallNumbers;
    std::array<sf::Sprite, 10> mediumNumbers;
    std::array<sf::Sprite, 10> largeNumbers;
};

#endif // ASSETLOADER_H
