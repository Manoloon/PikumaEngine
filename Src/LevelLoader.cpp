#include "LevelLoader.h"
#include "ECS/AssetStore.h"
#include "ECS/ECS.h"
#include "Game.h"
#include "GameGlobals.h"
#include <fstream>
#include <sol/sol.hpp>

void LevelLoader::LoadSettings(sol::state &LuaState, AssetStore *assetStore, int LevelNumber)
{
    const std::string scriptfile = "./assets/scripts/Level" + std::to_string(LevelNumber) + ".lua";
    sol::load_result script = LuaState.load_file(scriptfile);
    if (!script.valid())
    {
        sol::error err = script;
        std::string Message = err.what();
        Logger::Error(Message);
        return;
    }

    LuaState.safe_script_file(scriptfile.data());
    sol::table levelTable = LuaState["Level"];
    if (!levelTable.valid())
    {
        Logger::Error("Level table not found");
        return;
    }

    // Assets
    sol::table assetsTable = levelTable["assets"];
    if (!assetsTable.valid())
    {
        Logger::Error("Assets table not found");
        return;
    }

    for (int it = 0;; it++)
    {
        sol::optional<sol::table> asset = assetsTable[it];
        if (!asset)
        {
            Logger::Warning("Finished assets at index " + std::to_string(it));
            break;
        }

        //TODO : podria usarse un enum
        std::string assetType = (*asset)["type"];
        const std::string id = (*asset)["id"];
        const std::string assetFile = (*asset)["file"];
        if (assetType == "texture")
        {
            assetStore->AddTexture(id, assetFile);
            //Logger::Info("A new texture added id: " + id + " : " + assetFile);
        }
        else if (assetType == "font")
        {
            int size = (*asset)["font_size"];
            assetStore->AddFont(id, assetFile, size);
            //Logger::Info("A new Font added id: " + id);
        }
    }
    //// Level Assets

    /// level Tilemap
    sol::table map = levelTable["tilemap"];
    mapFile = map["map_file"];
    Logger::Info("map file " + mapFile);
    tilemapAssetID = map["texture_asset_id"];
    Logger::Info("tilemapAssetID " + tilemapAssetID);
    numRows = map["num_rows"];
    Logger::Info("num_rows " + std::to_string(numRows));
    numCols = map["num_cols"];
    Logger::Info("num_cols " + std::to_string(numCols));
    tileSize = map["tile_size"];
    Logger::Info("tileSize " + std::to_string(tileSize));
    tileScale = map["scale"];
    Logger::Info("tileScale" + std::to_string(tileScale));
    /// level tilemap

    
}

void LevelLoader::ParseNewMap(Registry *registry, int LevelNum)
{
    if (mapFile.empty())
    {
        Logger::Error("newMap string is empty");
        return;
    }
    std::fstream mapFileStream;
    mapFileStream.open(mapFile.data());
    if (mapFileStream.fail())
    {
        Logger::Error("Failed to read the tilemap.map file");
        exit(1);
    }
    const float tileWorldSize = tileScale * tileSize;
    for (int y = 0; y < numRows; y++)
    {
        for (int x = 0; x < numCols; x++)
        {
            char ch[2] = {0, 0};
            mapFileStream.get(ch[0]);
            const int srcRectY = std::atoi(&ch[0]) * tileSize;
            mapFileStream.get(ch[0]);
            const int srcRectX = std::atoi(&ch[0]) * tileSize;
            mapFileStream.ignore();

            Entity tile = registry->CreateEntity();
            // TODO : enum groups
            tile.Group("tiles");

            const sf::Vector2f tilePosition = {x * tileWorldSize, y * tileWorldSize};

            tile.AddComponent<CTransform>(tilePosition, sf::Vector2f(tileScale,tileScale), sf::degrees(0.0f));
            tile.AddComponent<CSprite>(tilemapAssetID,
                                       sf::Vector2f(tileSize, tileSize),
                                       ERenderLayers::L_TILEMAP,
                                       false,
                                       sf::Vector2f(srcRectX, srcRectY));
        }
    }
    mapFileStream.close();
    Game::mapWidth = numCols * tileWorldSize;
    Game::mapHeight = numRows * tileWorldSize;
    Game::viewSize = {640, 360};
}

void LevelLoader::LoadLevel(Registry *registry, int LevelID)
{
    ParseNewMap(registry, LevelID);

    // Entity Title = registry->CreateEntity();
    // Title.Group("UI");
    // Title.AddComponent<CTextComponent>(sf::Vector2f(10,10),"The Engine!","pico8-font-5",sf::Color::White);
    const sf::Vector2f newPos = sf::Vector2f(ScreenResWidth / 2.f, 300);
    Entity Tank = registry->CreateEntity();
    Tank.Group("Enemies");
    Tank.AddComponent<CTransform>(newPos, sf::Vector2f(2.0, 2.0), sf::degrees(0.f));
    Tank.AddComponent<CRigidBody>(sf::Vector2f(10.f, 0.f));
    Tank.AddComponent<CShootEmitter>(sf::Vector2f(50, 10), 100, 1000, false);
    Tank.AddComponent<CSprite>("tank-tiger-right-texture", sf::Vector2f(32.f, 32.f), ERenderLayers::L_ENEMIES);
    Tank.AddComponent<CHealth>(100);
    std::string TankhealthText = std::to_string(Tank.GetComponent<CHealth>().Health);
    sf::Vector2f Tankpos = {Tank.GetComponent<CTransform>().position.x,
                            Tank.GetComponent<CTransform>().position.y - 10};
    Tank.AddComponent<CTextComponent>(Tankpos, TankhealthText, "pico8-font-5", sf::Color::Green, 5, false);
    Tank.AddComponent<CBoxCollision>(sf::Vector2f(32.f, 32.f));

    Entity Truck = registry->CreateEntity();
    Truck.Group("Enemies");
    Truck.AddComponent<CTransform>(sf::Vector2f(200, 50), sf::Vector2f(1.0, 1.0), sf::degrees(0.f));
    Truck.AddComponent<CRigidBody>(sf::Vector2f(0.f, 0.f));
    Truck.AddComponent<CShootEmitter>(sf::Vector2f(40, 0), 100, 1000, false);
    Truck.AddComponent<CSprite>("truck-ford-right-texture", sf::Vector2f(32.f, 32.f), ERenderLayers::L_ENEMIES);
    Truck.AddComponent<CBoxCollision>(sf::Vector2f(32.f, 32.f));

    Entity Player = registry->CreateEntity();
    Player.Tag("Player");
    Player.AddComponent<CTransform>(newPos, sf::Vector2f(1.0, 1.0), sf::degrees(0.f));
    Player.AddComponent<CRigidBody>(sf::Vector2f(0.f, 0.f));
    Player.AddComponent<CSprite>("chopper-texture", sf::Vector2f(32.f, 32.f), ERenderLayers::L_PLAYER);
    Player.AddComponent<CAnimation>(2, 6);
    Player.AddComponent<CHealth>(100);
    Player.AddComponent<CCamera>(newPos, Game::viewSize);
    //velocity,loopFrequency,lifeSpan,damagePercentage,bIsFriendly,lastEmissionTime;
    Player.AddComponent<CShootEmitter>(sf::Vector2f(40.f, 40.f), 0, 10000, 10, true);
    Player.AddComponent<CKeyboardControlled>(500, 300, 0.95);
    Player.AddComponent<CBoxCollision>(sf::Vector2f(32.f, 32.f));

    Entity chop2 = registry->CreateEntity();
    chop2.Group("Enemies");
    chop2.AddComponent<CTransform>(sf::Vector2f(150, 150), sf::Vector2f(2.0, 2.0), sf::degrees(0.f));
    chop2.AddComponent<CRigidBody>(sf::Vector2f(0.f, 0.f));
    chop2.AddComponent<CSprite>("chopper-texture", sf::Vector2f(32.f, 32.f), ERenderLayers::L_ENEMIES);
    chop2.AddComponent<CAnimation>(2, 12);
    chop2.AddComponent<CBoxCollision>(sf::Vector2f(32.f, 32.f));

    Entity chop1 = registry->CreateEntity();
    chop1.Group("Enemies");
    chop1.AddComponent<CTransform>(sf::Vector2f(250, 250), sf::Vector2f(1.0, 1.0), sf::degrees(0.f));
    chop1.AddComponent<CRigidBody>(sf::Vector2f(0.f, 0.f));
    chop1.AddComponent<CSprite>("chopper-texture", sf::Vector2f(32.f, 32.f), ERenderLayers::L_ENEMIES);
    chop1.AddComponent<CAnimation>(2, 2);
    chop1.AddComponent<CHealth>();
    std::string healthText = std::to_string(chop1.GetComponent<CHealth>().Health);
    sf::Vector2f chop1pos = {chop1.GetComponent<CTransform>().position.x,
                             chop1.GetComponent<CTransform>().position.y - 10};
    chop1.AddComponent<CTextComponent>(chop1pos, healthText, "pico8-font-5", sf::Color::Green, 5);
    chop1.AddComponent<CBoxCollision>(sf::Vector2f(32.f, 32.f));

    Entity tree = registry->CreateEntity();
    tree.Group("Obstacles");
    tree.AddComponent<CTransform>(sf::Vector2f(5.f, 50.f));
    tree.AddComponent<CSprite>("tree2-texture", sf::Vector2f(16.f, 32.f), ERenderLayers::L_OBSTACLES);
    tree.AddComponent<CBoxCollision>(sf::Vector2f(16.f, 32.f));

    Entity tree2 = registry->CreateEntity();
    tree2.Group("Obstacles");
    tree2.AddComponent<CTransform>(sf::Vector2f(100.f, 50.f));
    tree2.AddComponent<CSprite>("tree1-texture", sf::Vector2f(16.f, 32.f), ERenderLayers::L_OBSTACLES);
    tree2.AddComponent<CBoxCollision>(sf::Vector2f(16.f, 32.f));

    Entity UI_Radar = registry->CreateEntity();
    UI_Radar.Group("UI");
    UI_Radar.AddComponent<CTransform>(sf::Vector2f(ScreenResWidth - 100.f, 50.f));
    UI_Radar.AddComponent<CSprite>("radar-texture", sf::Vector2f(64.f, 64.f), ERenderLayers::L_GUI, true);
    UI_Radar.AddComponent<CAnimation>(8, 5);
}

void LevelLoader::SetupAndLoad(Registry *registry, AssetStore *assetStore, sol::state &LuaState, int LevelID)
{
    LoadSettings(LuaState, assetStore, LevelID);
    LoadLevel(registry, LevelID);
}
