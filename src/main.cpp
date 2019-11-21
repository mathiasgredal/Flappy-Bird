#include <iostream>

#include <SFML/Graphics.hpp>

#include "AssetLoader.h"
#include "MapGenerator.h"
#include "Player.h"
#include "UI_Navigation.h"

using namespace std;

const float scale = 3.0f;

const int screenWidth = 288*scale;
const int screenHeight = 512*scale;


int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Flappy Bird");
    window.setFramerateLimit(60);


    AssetLoader assetLoader = AssetLoader(scale);
    MapGenerator mapGenerator = MapGenerator(scale, assetLoader);
    Player player = Player(scale, assetLoader);
    UI_Navigation ui = UI_Navigation(scale, assetLoader);

    bool keyIsDown = false;

    sf::Clock deltaClock;


    // run the program as long as the window is open
    while (window.isOpen())
    {
        float deltaTime = deltaClock.restart().asMilliseconds()/1000.f;
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();


            ui.HandleEvent(window, event, assetLoader);

            if(event.type == event.KeyPressed && !keyIsDown &&event.key.code == sf::Keyboard::Space)
            {
                keyIsDown = true;
                player.Jump();
            }

            if(event.type == event.KeyReleased && event.key.code == sf::Keyboard::Space)
            {
                keyIsDown = false;
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        switch(ui.uiState)
        {
        case MainMenu:
            mapGenerator.DrawMap(window, assetLoader);

            player.AnimatePlayer(deltaTime, assetLoader);
            player.DrawPlayer(window, assetLoader, ui.uiState);

            ui.DrawUI(window, deltaTime, assetLoader, mapGenerator);
            break;
        case PreGame:
            mapGenerator.DrawMap(window, assetLoader);
            player.AnimatePlayer(deltaTime, assetLoader);
            player.DrawPlayer(window, assetLoader, ui.uiState);
            ui.DrawUI(window, deltaTime, assetLoader, mapGenerator);

            break;
        case InGame:
            mapGenerator.UpdateMap(deltaTime, assetLoader);
            mapGenerator.DrawMap(window, assetLoader);
            player.AnimatePlayer(deltaTime, assetLoader);
            player.UpdatePlayer(deltaTime, assetLoader);
            player.DrawPlayer(window, assetLoader, ui.uiState);
            ui.DrawUI(window, deltaTime, assetLoader, mapGenerator);
            break;
        case GameOver:
            break;

        }



        // end the current frame
        window.display();
    }

    return 0;
}
