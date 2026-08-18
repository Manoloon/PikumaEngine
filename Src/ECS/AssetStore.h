//
// Created by Manoloon on 23/06/2022.
//

#ifndef PIKUMAENGINE_ASSETSTORE_H
#define PIKUMAENGINE_ASSETSTORE_H
#include <map>
#include <string_view>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio/Sound.hpp>

class AssetStore
{
    std::map<std::string,sf::Texture> textures;
   // std::map<std::string_view,>TilemapTiles;
    std::map<std::string,sf::Font> fonts;
    std::map<std::string,sf::Sound> audio;

public:
    AssetStore()=default;

    void ClearAssets();
    void AddTexture(std::string_view assetId,const std::string &filePath);
    void AddFont(std::string_view assetId,const std::string& filePath, unsigned int fontSize);
    sf::Texture* GetTexture(std::string_view assetId);
    sf::Font* GetFont(std::string_view assetId);
};
#endif //PIKUMAENGINE_ASSETSTORE_H
