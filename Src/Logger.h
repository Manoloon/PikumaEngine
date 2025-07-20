//
// Created by Manoloon on 17/05/2022.
//
#pragma once 

#include <string_view>
#include <chrono>
#include <iostream>

class Logger
{
public:
    // Logger::Warning("Shoot");
    static void Warning(const std::string_view &Message);
    // Logger::Error("DEAD");
    static void Error(const std::string_view &Message);
};
