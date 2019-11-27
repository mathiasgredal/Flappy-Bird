#include "MapGenerator.h"

MapGenerator::MapGenerator(const float _scale, const float _speed, AssetLoader& assetLoader) : scale(_scale), speed(_speed)
{
    assetLoader.ground.setPosition(0, assetLoader.backgroundDay.getGlobalBounds().height-assetLoader.ground.getGlobalBounds().height);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, assetLoader.backgroundDay.getGlobalBounds().height-assetLoader.ground.getGlobalBounds().height);


    for(int i = 0; i < 100; i++)
    {

        pipes.push_back(dist6(rng)); // distribution in range [1, 6]
    }
}

void MapGenerator::HandleNewState(sf::RenderWindow &window, AssetLoader &assetLoader, UI_State newState)
{
    if(newState == UI_State::PreGame)
    {
        distance = startDist;
        pipes.clear();
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> dist6(minimumPipeLength, assetLoader.backgroundDay.getGlobalBounds().height-assetLoader.ground.getGlobalBounds().height-minimumPipeLength);


        for(int i = 0; i < 100; i++)
        {

            pipes.push_back(dist6(rng)); // distribution in range [1, 6]
        }
    }
}

void MapGenerator::UpdateMap(float deltaTime, AssetLoader &assetLoader)
{
    distance += speed*deltaTime;

    assetLoader.ground.move(-speed*deltaTime,0);

    if(abs(assetLoader.ground.getPosition().x) > assetLoader.ground.getGlobalBounds().width)
    {
        assetLoader.ground.setPosition(0, assetLoader.backgroundDay.getGlobalBounds().height-assetLoader.ground.getGlobalBounds().height);
    }
}

void MapGenerator::DrawMap(sf::RenderWindow &window, AssetLoader& assetLoader, float deltaTime, UI_State uiState)
{
    if(uiState == UI_State::InGame)
    {
        UpdateMap(deltaTime, assetLoader);
    }

    window.draw(assetLoader.backgroundDay);

    for (int i = 0; i < pipes.size(); i++)
    {
        assetLoader.topPipe.setPosition(pipeDistance*i-distance, pipes.at(i));
        window.draw(assetLoader.topPipe);

        assetLoader.bottomPipe.setPosition(pipeDistance*i-distance, pipes.at(i)-pipeGap-assetLoader.bottomPipe.getGlobalBounds().height);
        window.draw(assetLoader.bottomPipe);
    }

    window.draw(assetLoader.ground);
    assetLoader.ground.move(assetLoader.ground.getGlobalBounds().width,0);
    window.draw(assetLoader.ground);
    assetLoader.ground.move(-assetLoader.ground.getGlobalBounds().width,0);
}
