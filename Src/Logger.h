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
    static void Info(std::string_view Message);
    // Logger::Warning("Shoot");
    static void Warning(std::string_view Message);
    // Logger::Error("DEAD");
    static void Error(std::string_view Message);
};
