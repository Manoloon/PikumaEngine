//
// Created by Manoloon on 17/05/2022.
//

#ifndef PIKUMAENGINE_LOGGER_H
#define PIKUMAENGINE_LOGGER_H
#include <string_view>
#include <chrono>
#include <iostream>

class Logger
{
public:
    static void Warning(const std::string_view &Message)
    {
        std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << "\x1b[1;32m" << std::ctime(&end_time) << Message << "\x1b[0;32m" <<
        "\x1b[0m" <<
        std::endl;
    };

    static void Error(const std::string_view &Message)
    {
        std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << "\x1b[1;31m" << std::ctime(&end_time) << Message << "\x1b[0;31m" <<
        "\x1b[0m" << std::endl;
    };
};
#endif //PIKUMAENGINE_LOGGER_H
