#include "AssetLoader.h"

AssetLoader::AssetLoader(const float scale)
{
    // Load main texture atlas

    if (!atlas.loadFromFile("Assets/atlas.png"))
    {
        assert(("Unable to find texture atlas in Assets folder", false));
    }

    backgroundDay.setTexture(atlas);
    backgroundDay.setTextureRect({0,0,288, 512});
    backgroundDay.setScale(scale, scale);

    backgroundNight.setTexture(atlas);

    ground.setTexture(atlas);
    ground.setTextureRect({584,0,336, 112});
    ground.setScale(scale, scale);


    topPipe.setTexture(atlas);
    topPipe.setTextureRect({0, 646, 52, 320});
    topPipe.setScale(scale, scale);

    bottomPipe.setTexture(atlas);
    bottomPipe.setTextureRect({112, 646, 52, 320});
    bottomPipe.setScale(scale, scale);

    for(int i = 0; i < bird.size(); i++)
    {
        bird[i].setTexture(atlas);
        bird[i].setScale(scale, scale);
    }

    bird[0].setTextureRect({230, 658, 34, 24});
    bird[1].setTextureRect({230, 710, 34, 24});
    bird[2].setTextureRect({230, 762, 34, 24});
    bird[3].setTextureRect({230, 814, 34, 24});
    bird[4].setTextureRect({230, 866, 34, 24});
    bird[5].setTextureRect({6, 982, 34, 24});
    bird[6].setTextureRect({62, 982, 34, 24});
    bird[7].setTextureRect({118, 982, 34, 24});
    bird[8].setTextureRect({174, 982, 34, 24});


    titleText.setTexture(atlas);
    titleText.setTextureRect({702, 182 ,178, 48});
    titleText.setScale(scale, scale);

    playButton.setTexture(atlas);
    playButton.setTextureRect({708, 236, 104, 58});
    playButton.setScale(scale, scale);

    scoreButton.setTexture(atlas);
    scoreButton.setTextureRect({828, 236, 104, 58});
    scoreButton.setScale(scale, scale);

    beginScreen.setTexture(atlas);
    beginScreen.setTextureRect({584, 182, 114, 98});
    beginScreen.setScale(scale, scale);

    beginText.setTexture(atlas);
    beginText.setTextureRect({590, 118, 184, 50});
    beginText.setScale(scale, scale);


    // Get numbers
    for(int i = 0; i < smallNumbers.size(); i++)
    {
        smallNumbers[i].setTexture(atlas);
        smallNumbers[i].setScale(scale, scale);
    }

    smallNumbers[0].setTextureRect({276, 646, 12, 14});
    smallNumbers[1].setTextureRect({282, 664, 6, 14});
    smallNumbers[2].setTextureRect({276, 698, 12, 14});
    smallNumbers[3].setTextureRect({276, 716, 12, 14});
    smallNumbers[4].setTextureRect({276, 750, 12, 14});
    smallNumbers[5].setTextureRect({276, 768, 12, 14});
    smallNumbers[6].setTextureRect({276, 802, 12, 14});
    smallNumbers[7].setTextureRect({276, 820, 12, 14});
    smallNumbers[8].setTextureRect({276, 854, 12, 14});
    smallNumbers[9].setTextureRect({276, 872, 12, 14});

    for(int i = 0; i < mediumNumbers.size(); i++)
    {
        mediumNumbers[i].setTexture(atlas);
        mediumNumbers[i].setScale(scale, scale);
    }

    mediumNumbers[0].setTextureRect({274 , 612 , 14, 20});
    mediumNumbers[1].setTextureRect({278 , 954 , 10, 20});
    mediumNumbers[2].setTextureRect({274 , 978 , 14, 20});
    mediumNumbers[3].setTextureRect({262 , 1002, 14, 20});
    mediumNumbers[4].setTextureRect({1004, 0   , 14, 20});
    mediumNumbers[5].setTextureRect({1004, 24  , 14, 20});
    mediumNumbers[6].setTextureRect({1010, 52  , 14, 20});
    mediumNumbers[7].setTextureRect({1010, 84  , 14, 20});
    mediumNumbers[8].setTextureRect({586 , 484 , 14, 20});
    mediumNumbers[9].setTextureRect({622 , 412 , 14, 20});

    for(int i = 0; i < largeNumbers.size(); i++)
    {
        largeNumbers[i].setTexture(atlas);
        largeNumbers[i].setScale(scale, scale);
    }

    largeNumbers[0].setTextureRect({992 , 120 , 24, 36});
    largeNumbers[1].setTextureRect({272 , 910 , 16, 36});
    largeNumbers[2].setTextureRect({584 , 320 , 24, 36});
    largeNumbers[3].setTextureRect({612 , 320, 24, 36});
    largeNumbers[4].setTextureRect({640,  320, 24, 36});
    largeNumbers[5].setTextureRect({668,  320, 24, 36});
    largeNumbers[6].setTextureRect({584,  368, 24, 36});
    largeNumbers[7].setTextureRect({584+28, 368  , 24, 36});
    largeNumbers[8].setTextureRect({584+2*28 , 368 , 24, 36});
    largeNumbers[9].setTextureRect({584+3*28 , 368 , 24, 36});

}
