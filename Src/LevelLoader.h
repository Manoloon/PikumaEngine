#pragma once
#include "Enums/EngineEnums.h"
#include <sol/sol.hpp>
class Registry;
class AssetStore;

class LevelLoader
{
    // TODO : temp ScreenWidth , this should be taken from Lua script
    float ScreenResWidth = 800.f;
    // helper functions
    ERenderLayers ParseRenderLayer(int layer);
    bool HasTable(const sol::table& table,const char* key);
    void LoadGameSettings(sol::state& LuaState,AssetStore* assetStore,int LevelNumber);
    void LoadEntities(Registry* registry);
    void LoadLevel(Registry* registry);
    void ParseNewMap(Registry* registry);
    /// @brief  Load the lua script file
    /// @param LuaState 
    /// @return true if success , false if not.
    bool LoadScript(sol::state& LuaState,int LevelNumber);
    /// @brief Load level from lua script 
    /// @param LuaState 
    /// @return if success : return true
    bool LoadLevelFromScript(sol::state &LuaState);
    /// @brief Load assets into assetStore from the lua script
    /// @param assetStore 
    /// @return true if success
    bool LoadAssetsFromScript(AssetStore *assetStore);
    sol::table levelTable;
    
    public:
    void SetupAndLoad(Registry* registry,AssetStore* assetStore,sol::state& LuaState,int LevelID = 1);
};