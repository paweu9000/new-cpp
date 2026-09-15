#include <iostream>
#include <string_view>
#include <string>
#include <fstream>
#include <filesystem>

#include <windows.h>
#undef ERROR

#include "template.hpp"
#include "constants.hpp"

namespace fs = std::filesystem;

namespace Template
{
    // PRIVATE
    const std::string NAME = "<NAME>";
    const std::string VERSION = "<VERSION>";

    fs::path getExecutablePath()
    {
        wchar_t buffer[MAX_PATH];
        DWORD len = GetModuleFileNameW(nullptr, buffer, MAX_PATH);
        if (len == 0 || len == MAX_PATH)
        {
            throw std::runtime_error("Failed to get executable path");
        }
        return fs::path(buffer);
    }

    std::string readFile(std::string path)
    {
        std::ifstream file{path};
        auto fileSize = file.seekg(0, std::ios::end).tellg();
        file.seekg(0);
        
        std::string fileContents{};
        fileContents.reserve(fileSize);

        std::string line;

        while (std::getline(file, line))
        {
            fileContents += line + '\n';
        }

        file.close();
        
        return fileContents;
    }

    void replaceData(const Types::Data& data, std::string& contents)
    {
        size_t startPos{0};
        while ((startPos = contents.find(NAME, startPos)) != std::string::npos)
        {
            contents.replace(startPos, NAME.length(), data.project_name);
            startPos += data.project_name.length();
        }
        startPos = 0;
        while ((startPos = contents.find(VERSION, startPos)) != std::string::npos)
        {
            contents.replace(startPos, VERSION.length(), std::to_string(data.version));
            startPos += std::to_string(data.version).length();
        }
    }

    // PUBLIC
    void generate(const Types::Data& data)
    {
        auto buildPath{Template::getExecutablePath().parent_path()};
        std::string mainContents{Template::readFile((buildPath / Constants::main_path).string())};
        std::string cmakeContents{Template::readFile((buildPath / Constants::cmake_path).string())};
        std::string buildScriptContents{Template::readFile((buildPath / Constants::script_path).string())};

        replaceData(data, mainContents);
        replaceData(data, cmakeContents);
        replaceData(data, buildScriptContents);
      
        auto path{fs::current_path()};
        
        fs::create_directory(path / "src");
        
        std::ofstream ofs(path / "src/main.cpp");
        ofs << mainContents;
        ofs = path / "CMakeLists.txt";
        ofs << cmakeContents;
        ofs = path / "run.ps1";
        ofs << buildScriptContents;
        ofs.close();
    }
};