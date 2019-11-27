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
const float speed = 100*scale;

bool DetectCollision(Player &player, MapGenerator& mapGenerator, AssetLoader& assetLoader)
{
    sf::Vector2f birdPos = assetLoader.bird[player.animationFrame].getPosition();
    int nextPipeIndex = floor((mapGenerator.distance)/mapGenerator.pipeDistance)+1;
    if(nextPipeIndex < 0)
        nextPipeIndex = 0;

    int currentPipeIndex = (mapGenerator.distance+assetLoader.bird[0].getPosition().x+mapGenerator.pipeDistance-assetLoader.bottomPipe.getGlobalBounds().width)/mapGenerator.pipeDistance;
    currentPipeIndex = (currentPipeIndex < 0)? 0 : currentPipeIndex;

    // birdPos.x+assetLoader.bird[player.animationFrame].getGlobalBounds().height


    // Top of bottom pipe
    //

    // Front of pipe
    if(mapGenerator.pipeDistance*currentPipeIndex < mapGenerator.distance+assetLoader.bird[0].getPosition().x+assetLoader.bird[0].getGlobalBounds().width)
    {
        if(mapGenerator.pipes[nextPipeIndex] < birdPos.y+assetLoader.bird[player.animationFrame].getGlobalBounds().height)
            return true;

        if(mapGenerator.pipes[nextPipeIndex]-mapGenerator.pipeGap > birdPos.y)
            return true;
    }

    if(assetLoader.bird[player.animationFrame].getPosition().y+assetLoader.bird[player.animationFrame].getGlobalBounds().height > assetLoader.backgroundDay.getGlobalBounds().height-assetLoader.ground.getGlobalBounds().height )
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "Flappy Bird");
    window.setFramerateLimit(60);


    AssetLoader assetLoader = AssetLoader(scale);
    MapGenerator mapGenerator = MapGenerator(scale, speed, assetLoader);
    Player player = Player(scale, speed, assetLoader);
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
                keyIsDown = false;

        }



        if(ui.StateChanged())
        {
            mapGenerator.HandleNewState(window, assetLoader, ui.uiState);
            player.HandleNewState(window, assetLoader, ui.uiState);
            ui.HandleNewState(window, assetLoader, ui.uiState);
        }

        // clear the window with black color
        window.clear(sf::Color::Black);


        mapGenerator.DrawMap(window, assetLoader, deltaTime, ui.uiState);
        player.DrawPlayer(window, assetLoader, deltaTime, ui.uiState);
        ui.DrawUI(window, deltaTime, assetLoader, mapGenerator);


        if(DetectCollision(player, mapGenerator, assetLoader) && ui.uiState == UI_State::InGame)
        {
            ui.ChangeState(UI_State::GameOver);
        }


        // end the current frame
        window.display();
    }

    return 0;
}
