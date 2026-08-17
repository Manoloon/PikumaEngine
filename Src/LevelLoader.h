#pragma once
#include <string_view>
class Registry;

class LevelLoader
{
    void ParseNewMap(Registry* registry,const std::string_view newMap);
    public:
    void LoadLevel(Registry* registry,float ScreenResWidth, int LevelID);
};