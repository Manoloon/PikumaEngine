#pragma once
#include <string_view>
#include <sol/sol.hpp>
class Registry;
class AssetStore;

class LevelLoader
{
    void LoadAssets(AssetStore* assetStore);
    void ParseNewMap(Registry* registry,const std::string_view newMap);
   
    public:
    void LoadSettings(sol::state& LuaState,int LevelNumber);
    void LoadLevel(Registry* registry,AssetStore* assetStore,float ScreenResWidth, int LevelID);
};