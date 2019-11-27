#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <iostream>
#include <vector>
#include <random>
#include "AssetLoader.h"
#include "UI_Navigation.h"


class MapGenerator
{
public:
    MapGenerator(const float _scale, const float _speed, AssetLoader& assetLoader);

    void HandleNewState(sf::RenderWindow &window, AssetLoader& assetLoader, UI_State newState);

    void DrawMap(sf::RenderWindow &window, AssetLoader& assetLoader, float deltaTime, UI_State uiState);
    void UpdateMap(float deltaTime, AssetLoader& assetLoader);

    // Map generation parameters
    const float scale;
    const float pipeDistance = 150*scale;
    const float pipeGap = 100.0f*scale;
    const float minimumPipeLength = 100*scale;

    const float speed;
    const float startDist = -300*scale;

    // Game Session info
    std::vector<int> pipes;
    float distance = startDist;
    MapGenerator();
    void Yeet();
};

#endif // MAPGENERATOR_H
