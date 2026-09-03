#include <iostream>
#include <string_view>
#include <array>
#include <string.h>
#include <string>
#include <stdexcept>

const std::string_view help_message{
    "---------------- HELP ------------------\n"
    "newcpp new {PROJECT_NAME} [CPP_VERSION]\n"
    "PROJECT_NAME - string name of the project i.e. MyProject\n"
    "CPP_VERSION (OPTIONAL, DEFAULT 17) - int version of CPP compiler i.e. 20\n"
    "Example: newcpp MyProject 23\n"
    "----------------------------------------\n"
};

const std::string_view bad_version_message{
    "----------- ERROR -----------\n"
    "Version must be an int\n"
    "Type 'newcpp help' for help\n"
    "-----------------------------\n"
};

const std::string_view bad_name_message{
    "----------- ERROR -----------\n"
    "Project name must be either\n"
    "new - for new  | help - for help\n"
    "-----------------------------\n"
};

const char* help_flag = "help";
const char* new_flag = "new";

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

int main(int argc, char* argv[])
{
    Data data{};

    for (int count{1}; count < argc; ++count)
    {
        switch (count)
        {
            case 1:
            {
                int valid{!strcmp(argv[count], new_flag) || !strcmp(argv[count], help_flag)};
                if (!valid)
                {
                    data.action = Action::ERROR;
                    data.error_message = bad_name_message;
                    break;
                }
                int is_new{!strcmp(new_flag, argv[count])};
                is_new ? (data.action = Action::NEW) : (data.action = Action::HELP);
                break;
            }
            case 2:
                data.project_name = argv[count];
                break;
            case 3:
            {
                try
                {
                    data.version = std::stoi(argv[count], 0);
                }
                catch (...)
                {
                    data.action = Action::ERROR;
                    data.error_message = bad_version_message;
                }
                break;
            }
            default:
                break;
        }
        if (data.action == Action::HELP || data.action == Action::ERROR) break;
    }

    if (data.action == Action::HELP)
    {
        std::cout << help_message;
    }
    else if (data.action == Action::ERROR)
    {
        std::cout << data.error_message;
    }
    else
    {
        std::cout << "Data: " << (int)data.action << " --- " << data.project_name << " --- " << data.version << '\n'; 
    }

    return 0;
}