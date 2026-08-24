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
    void ParseNewMap(Registry* registry,int LevelNum);

    std::string mapFile = "";
    std::string tilemapAssetID = "";
    int numRows = 1;
    int numCols = 1;
    int tileSize= 8;
    float tileScale = 1.f;

    public:
    void SetupAndLoad(Registry* registry,AssetStore* assetStore,sol::state& LuaState,int LevelID = 1);
};