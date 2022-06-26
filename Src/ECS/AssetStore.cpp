//
// Created by Manoloon on 23/06/2022.
//

#include "AssetStore.h"
#include <SFML/Graphics.hpp>

void AssetStore::ClearAssets()
{
    /*
    for(auto texture: textures)
    {
        sf::Texture:destroy(texture.second)
    }*/
    textures.clear();
}

void AssetStore::AddTexture(std::string_view assetId, const std::string &filePath)
{
    sf::Texture newTexture;
    newTexture.loadFromFile(filePath);
    textures.try_emplace(assetId,newTexture);
    // add the texture to the map with emplace (id,texture)
}
sf::Texture* AssetStore::GetTexture(std::string_view assetId)
{
    return &textures[assetId];
}
