#include <iostream>
#include <string_view>
#include <array>
#include <string.h>
#include <string>
#include <stdexcept>

#include "constants.hpp"
#include "types.hpp"
#include "template.hpp"

namespace T = Types;
namespace C = Constants;

int main(int argc, char* argv[])
{
    T::Data data{};

    for (int count{1}; count < argc; ++count)
    {
        switch (count)
        {
            case static_cast<int>(T::Flag::ACTION):
            {
                int valid{!strcmp(argv[count], C::new_flag) || !strcmp(argv[count], C::help_flag)};
                if (!valid)
                {
                    data.action = T::Action::ERROR;
                    data.error_message = C::bad_name_message;
                    break;
                }
                int is_new{!strcmp(C::new_flag, argv[count])};
                is_new ? (data.action = T::Action::NEW) : (data.action = T::Action::HELP);
                break;
            }
            case static_cast<int>(T::Flag::NAME):
                data.project_name = argv[count];
                break;
            case static_cast<int>(T::Flag::VERSION):
            {
                try
                {
                    data.version = std::stoi(argv[count], 0);
                }
                catch (...)
                {
                    data.action = T::Action::ERROR;
                    data.error_message = C::bad_version_message;
                }
                break;
            }
            default:
                break;
        }
        if (data.action == T::Action::HELP || data.action == T::Action::ERROR) break;
    }

    if (data.action == T::Action::HELP)
    {
        std::cout << C::help_message;
    }
    else if (data.action == T::Action::ERROR)
    {
        std::cout << data.error_message;
    }
    else
    {
        Template::generate(data);
    }

    return 0;
}