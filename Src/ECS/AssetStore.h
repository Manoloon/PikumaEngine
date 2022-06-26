//
// Created by Manoloon on 23/06/2022.
//

#ifndef PIKUMAENGINE_ASSETSTORE_H
#define PIKUMAENGINE_ASSETSTORE_H
#include <map>
#include <string_view>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/Sound.hpp>

class AssetStore
{
    std::map<std::string_view,sf::Texture> textures;
    std::map<std::string,sf::Font> fonts;
    std::map<std::string,sf::Sound> audio;

public:
    AssetStore()=default;

    void ClearAssets();
    void AddTexture(std::string_view assetId,const std::string &filePath);
    sf::Texture* GetTexture(std::string_view assetId);
};
#endif //PIKUMAENGINE_ASSETSTORE_H
