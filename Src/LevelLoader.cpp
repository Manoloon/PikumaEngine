#include "LevelLoader.h"
#include "ECS/AssetStore.h"
#include "ECS/ECS.h"
#include "Game.h"
#include "GameGlobals.h"
#include <fstream>
#include <sol/sol.hpp>

ERenderLayers LevelLoader::ParseRenderLayer(int layer)
{
    switch (layer)
    {
    case 0:
    //Logger::Warning(std::to_string(layer) + " layer :" + "L_BACKGROUND");
        return ERenderLayers::L_BACKGROUND;
    case 1:
    //Logger::Warning(std::to_string(layer) + " layer :" + "L_TILEMAP");
        return ERenderLayers::L_TILEMAP;
    case 2:
    //Logger::Warning(std::to_string(layer) + " layer :" + "L_OBSTACLES");
        return ERenderLayers::L_OBSTACLES;
    case 3:
    //Logger::Warning(std::to_string(layer) + " layer :" + "L_ENEMIES");
        return ERenderLayers::L_ENEMIES;
    case 4:
    //Logger::Warning(std::to_string(layer) + " layer :" + "L_PROJECTILE");
        return ERenderLayers::L_PROJECTILE;
    case 5:
    //Logger::Warning(std::to_string(layer) + " layer :" + "L_PLAYER");
        return ERenderLayers::L_PLAYER;
    case 6:
    //Logger::Warning(std::to_string(layer) + " layer :" + "L_FOREGROUND");
        return ERenderLayers::L_FOREGROUND;
    case 7:
    //Logger::Warning(std::to_string(layer) + " layer :" + "L_GUI");
        return ERenderLayers::L_GUI;
    default:
    //Logger::Error("Invalid render layer: " +  std::to_string(layer));
        return ERenderLayers::L_GUI;
    }
}

bool LevelLoader::HasTable(const sol::table &table, const char *key)
{
    sol::object object = table[key];
    return object.valid() && object.get_type() == sol::type::table;
}

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
    levelTable = LuaState["Level"];
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
    tilemapAssetID = map["texture_asset_id"];
    numRows = map["num_rows"];
    numCols = map["num_cols"];
    tileSize = map["tile_size"];
    tileScale = map["scale"];
    /// level tilemap
}

void LevelLoader::LoadEntities(Registry *registry)
{
    sol::table entities = levelTable["entities"];
    for (int it = 0;; it++)
    {
        sol::optional<sol::table> hasEntity = entities[it];
        if (hasEntity == sol::nullopt)
        {
            Logger::Warning("Finished Entity at index " + std::to_string(it));
            break;
        }
        sol::table entity = *hasEntity;
        Entity newEntity = registry->CreateEntity();
        // Tag
        sol::optional<std::string> tag = entity["tag"];
        if (tag != sol::nullopt)
        {
            newEntity.Tag(*tag);
        }
        // components
        sol::optional<sol::table> hasComponent = entity["components"];
        if (hasComponent != sol::nullopt)
        {
            sol::table comps = *hasComponent;
            // Transform
            if (HasTable(comps, "transform"))
            {
                // TODO :ver si hace falta un get_or
                const sf::Vector2f newPos = {comps["transform"]["position"]["x"].get_or(0.f),
                                             comps["transform"]["position"]["y"].get_or(0.f)};
                const sf::Vector2f newScale = {comps["transform"]["scale"]["x"].get_or(1.f),
                                               comps["transform"]["scale"]["y"].get_or(1.f)};
                const float newRot = comps["transform"]["rotation"].get_or(0.f);
                newEntity.AddComponent<CTransform>(newPos, newScale, sf::degrees(newRot));
            }
            // Rigidbody
            if (HasTable(comps, "rigidbody"))
            {
                sol::table rigidbody = comps["rigidbody"];
                newEntity.AddComponent<CRigidBody>(
                    sf::Vector2f(rigidbody["velocity"]["x"].get_or(0.f), rigidbody["velocity"]["y"].get_or(0.f)));
            }
            // Sprite
            if (HasTable(comps, "sprite"))
            {
                sol::table table = comps["sprite"];
                const std::string asset_id = table["texture_asset_id"];
                int layer = table["z_index"];
                newEntity.AddComponent<CSprite>(
                    asset_id,
                    sf::Vector2f(table["width"].get_or(32.f), table["height"].get_or(32.f)),
                    ParseRenderLayer(layer),
                    table["fixed"].get_or(false),
                    sf::Vector2f(table["src_rect_x"].get_or(0.f), table["src_rect_y"].get_or(0.f)));
            }
            // Animation
            if (HasTable(comps, "animation"))
            {
                sol::table table = comps["animation"];
                newEntity.AddComponent<CAnimation>(table["num_frames"], table["speed_rate"], table["should_loop"].get_or(true));
            }
            // Collision
            if (HasTable(comps, "boxcollider"))
            {
                sol::table table = comps["boxcollider"];
                newEntity.AddComponent<CBoxCollision>(
                    sf::Vector2f(table["width"].get_or(1.f), table["height"].get_or(1.f)),
                    sf::Vector2f(table["offset"]["x"].get_or(0.f), table["offset"]["y"].get_or(0.f)));
            }
            // Health
            if (HasTable(comps, "health"))
            {
                newEntity.AddComponent<CHealth>(entity["components"]["health"]["health_percentage"].get_or(100));
            }
            // Projectile Emitter
            if (HasTable(comps, "projectile_emitter"))
            {

                newEntity.AddComponent<CShootEmitter>(
                    sf::Vector2f(entity["components"]["projectile_emitter"]["velocity"]["x"].get_or(100.f),
                                 entity["components"]["projectile_emitter"]["velocity"]["y"].get_or(100.f)),
                    entity["components"]["projectile_emitter"]["repeat_frequency"].get_or(0),
                    entity["components"]["projectile_emitter"]["duration"].get_or(10),
                    entity["components"]["projectile_emitter"]["hit_percentage_damage"].get_or(10000.f),
                    entity["components"]["projectile_emitter"]["friendly"].get_or(false));
            }
            // Keyboard Controller
            if (HasTable(comps, "keyboard_controller"))
            {
                newEntity.AddComponent<CKeyboardControlled>(entity["components"]["keyboard_controller"]["acceleration"],
                                                            entity["components"]["keyboard_controller"]["max_speed"],
                                                            entity["components"]["keyboard_controller"]["damping"]);
            }
            // Camera
            if (HasTable(comps, "camera_follow"))
            {
                newEntity.AddComponent<CCamera>(
                    sf::Vector2f(entity["components"]["camera_follow"]["position"]["x"].get_or(0.f),
                                 entity["components"]["camera_follow"]["position"]["y"].get_or(0.f)),
                    sf::Vector2u(entity["components"]["camera_follow"]["view_size"]["width"].get_or(200),
                                 entity["components"]["camera_follow"]["view_size"]["height"].get_or(200)));
            }
            // Scripting
            if (HasTable(comps, "on_update_script"))
            {
                sol::function func = comps["on_update_script"][0];
                Logger::Info("Script comp : func is valid? " + std::to_string(func.valid()));
                newEntity.AddComponent<CScript>(func);
            }
        }
    }
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

            tile.AddComponent<CTransform>(tilePosition, sf::Vector2f(tileScale, tileScale), sf::degrees(0.0f));
            tile.AddComponent<CSprite>(tilemapAssetID,
                                       sf::Vector2f(tileSize, tileSize),
                                       ERenderLayers::L_BACKGROUND,
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
    LoadEntities(registry);
}

void LevelLoader::SetupAndLoad(Registry *registry, AssetStore *assetStore, sol::state &LuaState, int LevelID)
{
    LoadSettings(LuaState, assetStore, LevelID);
    LoadLevel(registry, LevelID);
}
