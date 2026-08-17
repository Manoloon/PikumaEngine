#pragma once
#include <string_view>
class Registry;
class AssetStore;

class LevelLoader
{
    void LoadSettings();
    void LoadAssets(AssetStore* assetStore);
    void ParseNewMap(Registry* registry,const std::string_view newMap);
   
    public:
    void LoadLevel(Registry* registry,AssetStore* assetStore,float ScreenResWidth, int LevelID);
};