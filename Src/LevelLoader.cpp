#include "LevelLoader.h"
#include <fstream>
#include "Game.h"
#include "ECS/ECS.h"
#include "ECS/AssetStore.h"
#include "GameGlobals.h"
#include <sol/sol.hpp>

void LevelLoader::LoadSettings(sol::state& LuaState,AssetStore* assetStore, int LevelNumber)
{
    const std::string scriptfile = "./assets/scripts/Level" + std::to_string(LevelNumber) + ".lua";
    sol::load_result script = LuaState.load_file(scriptfile);
    if(!script.valid())
    {
        sol::error err = script;
        std::string Message = err.what();
        Logger::Error(Message);
        return;
    }

    LuaState.safe_script_file(scriptfile.data()); 
    sol::table levelTable = LuaState["Level"];
    if(!levelTable.valid())
    {
        Logger::Error("Level table not found");
        return;
    }

    // Assets
    sol::table assetsTable = levelTable["assets"];
    if(!assetsTable.valid())
    {
        Logger::Error("Assets table not found");
        return;
    }

    for(int it = 0; ;it++)
    {
        sol::optional<sol::table> asset = assetsTable[it];
        if(!asset)
        {
            Logger::Warning("Finished assets at index " + std::to_string(it));
            break;
        }

        //TODO : podria usarse un enum
        std::string assetType = (*asset)["type"];
        const std::string id = (*asset)["id"]; 
        const std::string assetFile = (*asset)["file"];
        if(assetType == "texture")
        {
            assetStore->AddTexture(id,assetFile);
            //Logger::Info("A new texture added id: " + id + " : " + assetFile);
        }
        else if (assetType == "font")
        {
            int size = (*asset)["font_size"];
            assetStore->AddFont(id,assetFile,size);
            //Logger::Info("A new Font added id: " + id);
        }
    }
    //// Level Assets
}


void LevelLoader::ParseNewMap(Registry* registry, const std::string_view newMap)
{
    if(newMap.empty())
    {
        Logger::Error("newMap string is empty");
        return;
    }
    std::fstream mapFile;
    mapFile.open(newMap.data());
    if(mapFile.fail())
    {
        Logger::Error("Failed to read the tilemap.map file");
        exit(1);
    }
    
    for(int y=0;y<MAP_ROWS;y++)
        {
            for(int x=0;x<MAP_COLUMNS;x++)
            {
                char ch[2]={0,0};
                mapFile.get(ch[0]);
                int srcRectY=std::atoi(&ch[0]) * (int)TILE_SIZE;
                mapFile.get(ch[0]);
                int srcRectX=std::atoi(&ch[0]) * (int)TILE_SIZE;
                mapFile.ignore();

                Entity tile = registry->CreateEntity();
                // TODO : enum groups
                tile.Group("tiles");
                tile.AddComponent<CTransform>(sf::Vector2f(x * (TILE_SCALE * TILE_SIZE),
                                                              y * (TILE_SCALE * TILE_SIZE)),
                                              sf::Vector2f(TILE_SCALE,TILE_SCALE),
                                              sf::degrees(0.0f));
                tile.AddComponent<CSprite>("tilemap-image",
                                           sf::Vector2f(TILE_SIZE,TILE_SIZE),
                                           ERenderLayers::L_TILEMAP, false,
                                           sf::Vector2f(srcRectX,srcRectY));
            }
        }
        mapFile.close();
        Game::mapWidth = MAP_COLUMNS * TILE_SIZE * TILE_SCALE;
        Game::mapHeight = MAP_ROWS * TILE_SIZE * TILE_SCALE;
}

void LevelLoader::LoadLevel(Registry* registry,int LevelID)
{
    // TODO : temporary
    const std::string_view map = "../assets/tilemaps/jungle.map";
    ParseNewMap(registry,map);

    // Entity Title = registry->CreateEntity();
    // Title.Group("UI");
    // Title.AddComponent<CTextComponent>(sf::Vector2f(10,10),"The Engine!","pico8-font-5",sf::Color::White);

    Entity Tank = registry->CreateEntity();
    Tank.Group("Enemies");
    Tank.AddComponent<CTransform>(sf::Vector2f(10, 50), sf::Vector2f(2.0, 2.0), sf::degrees(0.f));
    Tank.AddComponent<CRigidBody>(sf::Vector2f(10.f, 0.f));
    Tank.AddComponent<CShootEmitter>(sf::Vector2f(50,10),100,1000,false);
    Tank.AddComponent<CSprite>("tank-image", sf::Vector2f(32.f, 32.f), ERenderLayers::L_ENEMIES);
    Tank.AddComponent<CHealth>(100);
    std::string TankhealthText = std::to_string(Tank.GetComponent<CHealth>().Health);
    sf::Vector2f Tankpos = {Tank.GetComponent<CTransform>().position.x,Tank.GetComponent<CTransform>().position.y - 10} ;
    Tank.AddComponent<CTextComponent>(Tankpos,TankhealthText,"pico8-font-5",sf::Color::Green,5,false);
    Tank.AddComponent<CBoxCollision>(sf::Vector2f(32.f, 32.f));

    Entity Truck = registry->CreateEntity();
    Truck.Group("Enemies");
    Truck.AddComponent<CTransform>(sf::Vector2f(200, 50), sf::Vector2f(1.0, 1.0), sf::degrees(0.f));
    Truck.AddComponent<CRigidBody>(sf::Vector2f(0.f, 0.f));
    Truck.AddComponent<CShootEmitter>(sf::Vector2f(40,0),100,1000,false);
    Truck.AddComponent<CSprite>("truck-image", sf::Vector2f(32.f, 32.f), ERenderLayers::L_ENEMIES);
    Truck.AddComponent<CBoxCollision>(sf::Vector2f(32.f, 32.f));

    Entity Player = registry->CreateEntity();
    Player.Tag("Player");
    Player.AddComponent<CTransform>(sf::Vector2f(ScreenResWidth/2.f, 300), sf::Vector2f(1.0, 1.0), sf::degrees(0.f));
    Player.AddComponent<CRigidBody>(sf::Vector2f(0.f, 0.f));
    Player.AddComponent<CSprite>("player-image", sf::Vector2f(32.f, 32.f), ERenderLayers::L_PLAYER);
    Player.AddComponent<CAnimation>(2, 6);
    Player.AddComponent<CHealth>(100);
    Player.AddComponent<CCamera>();
    //velocity,loopFrequency,lifeSpan,damagePercentage,bIsFriendly,lastEmissionTime;
    Player.AddComponent<CShootEmitter>(sf::Vector2f(40.f,40.f),0,10000,10,true);
    Player.AddComponent<CKeyboardControlled>(500,300,0.95);
    Player.AddComponent<CBoxCollision>(sf::Vector2f(32.f, 32.f));
    Entity chop2 = registry->CreateEntity();
    chop2.Group("Enemies");
    chop2.AddComponent<CTransform>(sf::Vector2f(150, 150), sf::Vector2f(2.0, 2.0), sf::degrees(0.f));
    chop2.AddComponent<CRigidBody>(sf::Vector2f(0.f, 0.f));
    chop2.AddComponent<CSprite>("player-image", sf::Vector2f(32.f, 32.f), ERenderLayers::L_ENEMIES);
    chop2.AddComponent<CAnimation>(2, 12);
    chop2.AddComponent<CBoxCollision>(sf::Vector2f(32.f, 32.f));

    Entity chop1 = registry->CreateEntity();
    chop1.Group("Enemies");
    chop1.AddComponent<CTransform>(sf::Vector2f(250, 250), sf::Vector2f(1.0, 1.0), sf::degrees(0.f));
    chop1.AddComponent<CRigidBody>(sf::Vector2f(0.f, 0.f));
    chop1.AddComponent<CSprite>("player-image", sf::Vector2f(32.f, 32.f), ERenderLayers::L_ENEMIES);
    chop1.AddComponent<CAnimation>(2, 2);
    chop1.AddComponent<CHealth>();
    std::string healthText = std::to_string(chop1.GetComponent<CHealth>().Health);
    sf::Vector2f chop1pos = {chop1.GetComponent<CTransform>().position.x,chop1.GetComponent<CTransform>().position.y - 10} ;
    chop1.AddComponent<CTextComponent>(chop1pos,healthText,"pico8-font-5",sf::Color::Green,5);
    chop1.AddComponent<CBoxCollision>(sf::Vector2f(32.f, 32.f));

    Entity tree = registry->CreateEntity();
    tree.Group("Obstacles");
    tree.AddComponent<CTransform>(sf::Vector2f(5.f,50.f));
    tree.AddComponent<CSprite>("tree-image",sf::Vector2f(16.f,32.f),ERenderLayers::L_OBSTACLES);
    tree.AddComponent<CBoxCollision>(sf::Vector2f(16.f, 32.f));

    Entity tree2 = registry->CreateEntity();
    tree2.Group("Obstacles");
    tree2.AddComponent<CTransform>(sf::Vector2f(100.f,50.f));
    tree2.AddComponent<CSprite>("tree-image",sf::Vector2f(16.f,32.f),ERenderLayers::L_OBSTACLES);
    tree2.AddComponent<CBoxCollision>(sf::Vector2f(16.f, 32.f));

    Entity UI_Radar = registry->CreateEntity();
    UI_Radar.Group("UI");
    UI_Radar.AddComponent<CTransform>(sf::Vector2f(ScreenResWidth - 100.f, 50.f));
    UI_Radar.AddComponent<CSprite>("radar-image", sf::Vector2f(64.f, 64.f),
                                   ERenderLayers::L_GUI, true);
    UI_Radar.AddComponent<CAnimation>(8, 5);
}

void LevelLoader::SetupAndLoad(Registry *registry, AssetStore *assetStore, sol::state &LuaState, int LevelID)
{
    LoadSettings(LuaState,assetStore,LevelID);
    LoadLevel(registry,LevelID);
}
