//
// Created by Manoloon on 23/06/2022.
//

#include "AssetStore.h"
#include "Logger.h"
#include <SFML/Graphics.hpp>

void AssetStore::ClearAssets()
{
    /*
    for(auto texture: textures)
    {
        sf::Texture:destroy(texture.second)
    }*/
    textures.clear();
    fonts.clear();
}

void AssetStore::AddTexture(std::string_view assetId, const std::string &filePath)
{
    sf::Texture newTexture;
    if (!newTexture.loadFromFile(filePath))
    {
        Logger::Error("Failed to load texture: " + filePath);
        return;
    }
    textures.try_emplace(std::string(assetId),newTexture);
    //Logger::Info("Texture loaded: " + std::string(assetId));
}
void AssetStore::AddFont(std::string_view assetId, const std::string &filePath, unsigned int fontSize)
{
    sf::Font newFont;
    if(!newFont.openFromFile(filePath))
    {
        Logger::Error("Failed to load Font: " + filePath);
        return;
    }
    fonts.try_emplace(std::string(assetId),newFont);
}
sf::Texture *AssetStore::GetTexture(std::string_view assetId)
{
    auto it = textures.find(std::string(assetId));
    if(it == textures.end())
    {
        Logger::Error("Texture not found: " + std::string(assetId));
        return nullptr;
    }
    return &it->second;
}

sf::Font *AssetStore::GetFont(std::string_view assetId)
{
    auto it = fonts.find(std::string(assetId));
    if(it == fonts.end())
    {
        Logger::Error("font not found: " + std::string(assetId));
        return nullptr;
    }
    return &it->second;
}
