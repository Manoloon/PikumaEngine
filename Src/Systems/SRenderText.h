//
// Created by Manoloon on 22/06/2022.
//
#pragma once
#include "../ECS/ECS.h"
class AssetStore;
class SRenderText : public System
{
    public:
    SRenderText();
    void Initialize(AssetStore* assetStore);
    void Update(AssetStore* assetStore);
    void Draw(sf::RenderWindow& window,AssetStore* assetStore);
};