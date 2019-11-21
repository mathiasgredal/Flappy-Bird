#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include <iostream>
#include <vector>
#include <random>
#include "AssetLoader.h"


class MapGenerator
{
public:
    MapGenerator(const float _scale, AssetLoader& assetLoader);

    void DrawMap(sf::RenderWindow &window, AssetLoader& assetLoader);
    void UpdateMap(float deltaTime, AssetLoader& assetLoader);

    bool DetectCollision(AssetLoader& assetLoader);

    // Map generation parameters
    const float scale;
    const float pipeDistance = 150*scale;
    const float pipeGap = 100.0f*scale;
    const float minimumPipeLength = 100*scale;

    const float speed = 75*scale;

    // Game Session info
    std::vector<int> pipes;
    float distance = -1000;
    MapGenerator();
};

#endif // MAPGENERATOR_H
