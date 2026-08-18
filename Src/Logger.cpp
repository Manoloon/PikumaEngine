#include "Logger.h"

void Logger::Info(std::string_view Message)
{
        std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << "\x1b[1;32m" << std::ctime(&end_time) << Message << "\x1b[0;30m" <<
        "\x1b[0m" <<
        std::endl;  
}

void Logger::Warning(std::string_view Message)
{
        std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << "\x1b[1;32m" << std::ctime(&end_time) << Message << "\x1b[0;32m" <<
        "\x1b[0m" <<
        std::endl;
}

void Logger::Error(std::string_view Message) 
{
        std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << "\x1b[1;31m" << std::ctime(&end_time) << Message << "\x1b[0;31m" <<
        "\x1b[0m" << std::endl;
}
