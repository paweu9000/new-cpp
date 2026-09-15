#pragma once
#include <string_view>
#include <string>

namespace Types
{
    enum class Action
    {
        HELP,
        NEW,
        ERROR
    };

    struct Data
    {
        Action action;
        std::string project_name{};
        int version{17}; 
        std::string_view error_message{};
    };

    enum class Flag
    {
        ACTION = 1,
        NAME = 2,
        VERSION = 3
    };
}