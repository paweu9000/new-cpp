#pragma once
#include <string_view>
#include <string>

namespace Constants
{
    inline const std::string_view help_message{
        "---------------- HELP ------------------\n"
        "newcpp new {PROJECT_NAME} [CPP_VERSION]\n"
        "PROJECT_NAME - string name of the project i.e. MyProject\n"
        "CPP_VERSION (OPTIONAL, DEFAULT 17) - int version of CPP compiler i.e. 20\n"
        "Example: newcpp new MyProject 23\n"
        "----------------------------------------\n"
    };

    inline const std::string_view bad_version_message{
        "----------- ERROR -----------\n"
        "Version must be an int\n"
        "Type 'newcpp help' for help\n"
        "-----------------------------\n"
    };

    inline const std::string_view bad_name_message{
        "----------- ERROR -----------\n"
        "Project name must be either\n"
        "new - for new  | help - for help\n"
        "-----------------------------\n"
    };

    inline const char* help_flag{"help"};
    inline const char* new_flag{"new"};

    inline const std::string script_path{"./templates/BuildScriptTemplate.txt"};
    inline const std::string cmake_path{"./templates/CMakeTemplate.txt"};
    inline const std::string main_path{"./templates/MainTemplate.txt"};

    inline const std::string_view name_flag_placeholder{"<NAME>"};
    inline const std::string_view version_flag_placeholder{"<VERSION>"};

}