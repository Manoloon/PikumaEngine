#include "LevelLoader.h"
#include <fstream>
#include "Game.h"
#include "ECS/ECS.h"
#include "ECS/AssetStore.h"
#include "GameGlobals.h"


void LevelLoader::LoadSettings()
{
    
}

void LevelLoader::LoadAssets(AssetStore *assetStore)
{
    if(assetStore == nullptr)
    {
        Logger::Error("Failed to access to AssetStore pointer");
        return;
    }
    assetStore->AddTexture("tank-image","../assets/images/tank-panther-right.png");
    assetStore->AddTexture("truck-image","../assets/images/truck-ford-right.png");
    assetStore->AddTexture("player-image","../assets/images/chopper-spritesheet.png");
    assetStore->AddTexture("radar-image","../assets/images/radar.png");
    assetStore->AddTexture("tilemap-image","../assets/tilemaps/jungle.png");
    assetStore->AddTexture("bullet-image","../assets/images/bullet.png");
    assetStore->AddTexture("tree-image","../assets/images/tree.png");

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
                tile.Group("tiles");
                tile.AddComponent<CTransform>(sf::Vector2f(x * (TILE_SCALE * TILE_SIZE),
                                                              y * (TILE_SCALE * TILE_SIZE)),
                                              sf::Vector2f(TILE_SCALE,TILE_SCALE),
                                              0.0f);
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

void LevelLoader::LoadLevel(Registry* registry,AssetStore* assetStore,float ScreenResWidth,int LevelID)
{
    LoadAssets(assetStore);
    // TODO : temporary
    const std::string_view map = "../assets/tilemaps/jungle.map";
    ParseNewMap(registry,map);

    Entity Tank = registry->CreateEntity();
    Tank.Group("Enemies");
    Tank.AddComponent<CTransform>(sf::Vector2f(10, 50), sf::Vector2f(2.0, 2.0), 0.0);
    Tank.AddComponent<CRigidBody>(sf::Vector2f(10.f, 0.f));
    Tank.AddComponent<CShootEmitter>(sf::Vector2f(50,10),2000,2000,false);
    Tank.AddComponent<CSprite>("tank-image", sf::Vector2f(32.f, 32.f), ERenderLayers::L_ENEMIES);
    Tank.AddComponent<CBoxCollision>(sf::Vector2f(32.f, 32.f));

    Entity Truck = registry->CreateEntity();
    Truck.Group("Enemies");
    Truck.AddComponent<CTransform>(sf::Vector2f(200, 50), sf::Vector2f(1.0, 1.0), 0.0);
    Truck.AddComponent<CRigidBody>(sf::Vector2f(0.f, 0.f));
    Truck.AddComponent<CShootEmitter>(sf::Vector2f(40,0),5000,1000,false);
    Truck.AddComponent<CSprite>("truck-image", sf::Vector2f(32.f, 32.f), ERenderLayers::L_ENEMIES);
    Truck.AddComponent<CBoxCollision>(sf::Vector2f(32.f, 32.f));

    Entity Player = registry->CreateEntity();
    Player.Tag("Player");
    Player.AddComponent<CTransform>(sf::Vector2f(50, 50), sf::Vector2f(4.0, 4.0), 0.0);
    Player.AddComponent<CRigidBody>(sf::Vector2f(0.f, 0.f));
    Player.AddComponent<CSprite>("player-image", sf::Vector2f(32.f, 32.f), ERenderLayers::L_PLAYER);
    Player.AddComponent<CAnimation>(2, 6);
    Player.AddComponent<CHealth>(100);
    Player.AddComponent<CCameraFollow>();
    Player.AddComponent<CShootEmitter>(sf::Vector2f(40.f,40.f),0,1000,10,true,0);
    Player.AddComponent<CKeyboardControlled>(sf::Vector2f(0, -PLAYER_VELOCITY),
                                             sf::Vector2f(PLAYER_VELOCITY,0),
                                             sf::Vector2f(0,PLAYER_VELOCITY),
                                             sf::Vector2f(-PLAYER_VELOCITY,0));
    Player.AddComponent<CBoxCollision>(sf::Vector2f(32.f, 32.f));

    Entity chop2 = registry->CreateEntity();
    chop2.Group("Enemies");
    chop2.AddComponent<CTransform>(sf::Vector2f(150, 150), sf::Vector2f(2.0, 2.0), 0.0);
    chop2.AddComponent<CRigidBody>(sf::Vector2f(0.f, 0.f));
    chop2.AddComponent<CSprite>("player-image", sf::Vector2f(32.f, 32.f), ERenderLayers::L_ENEMIES);
    chop2.AddComponent<CAnimation>(2, 12);
    chop2.AddComponent<CBoxCollision>(sf::Vector2f(32.f, 32.f));

    Entity chop1 = registry->CreateEntity();
    chop1.Group("Enemies");
    chop1.AddComponent<CTransform>(sf::Vector2f(250, 250), sf::Vector2f(1.0, 1.0), 0.0);
    chop1.AddComponent<CRigidBody>(sf::Vector2f(0.f, 0.f));
    chop1.AddComponent<CSprite>("player-image", sf::Vector2f(32.f, 32.f), ERenderLayers::L_ENEMIES);
    chop1.AddComponent<CAnimation>(2, 2);
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
    UI_Radar.AddComponent<CTransform>(sf::Vector2f(ScreenResWidth - 100.f, 50.f));
    UI_Radar.AddComponent<CSprite>("radar-image", sf::Vector2f(64.f, 64.f),
                                   ERenderLayers::L_GUI, true);
    UI_Radar.AddComponent<CAnimation>(8, 5);
}
