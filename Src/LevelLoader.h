#pragma once
#include <string_view>
#include <sol/sol.hpp>
class Registry;
class AssetStore;

class LevelLoader
{
    // TODO : temp ScreenWidth , this should be taken from Lua script
    float ScreenResWidth = 800.f;
    void LoadSettings(sol::state& LuaState,AssetStore* assetStore,int LevelNumber);
    void LoadLevel(Registry* registry,int LevelID);
    void ParseNewMap(Registry* registry,const std::string_view newMap);
    public:
    void SetupAndLoad(Registry* registry,AssetStore* assetStore,sol::state& LuaState,int LevelID = 1);
};