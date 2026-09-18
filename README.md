# new-cpp

A small Windows command-line tool that scaffolds a new C++ project — generating a `src/main.cpp`, a `CMakeLists.txt`, and a PowerShell build script — so you can go from zero to a compiling "Hello, world!" in one command.

## Features

- Generates a minimal, ready-to-build C++ project structure
- Lets you pick the C++ standard version (defaults to C++17)
- Ships a PowerShell build script (`run.ps1`) that configures and builds the project with CMake + MinGW
- Single self-contained executable — templates are copied alongside it at build time

## Requirements

- Windows (the tool uses the Win32 API to locate its own executable path)
- [CMake](https://cmake.org/) 3.10+
- A C++23-capable compiler (e.g. MinGW-w64 `g++`) to build `newcpp` itself

## Building newcpp

```powershell
git clone https://github.com/paweu9000/new-cpp.git
cd new-cpp
cmake -G "MinGW Makefiles" -B build
cmake --build build
```

The build copies the `templates/` folder next to the resulting `newcpp.exe`, so keep the two together (or re-copy `templates/` if you move the executable).

## Usage

```
newcpp new <PROJECT_NAME> [CPP_VERSION]
```

| Argument       | Required | Description                                              |
|----------------|----------|------------------------------------------------------------|
| `PROJECT_NAME` | Yes      | Name of the project to generate, e.g. `MyProject`         |
| `CPP_VERSION`  | No       | C++ standard to target as an integer, e.g. `20` (defaults to `17`) |

Running `new` creates the following in your current directory:

```
.
├── src/
│   └── main.cpp        # "Hello world!" starter file
├── CMakeLists.txt       # Configured with your project name and C++ version
└── run.ps1              # Configures and builds the new project with CMake + MinGW
```

### Examples

Create a project called `MyProject` using the default C++ standard (17):

```powershell
newcpp new MyProject
```

Create a project called `MyProject` targeting C++23:

```powershell
newcpp new MyProject 23
```

### Help

```powershell
newcpp help
```

```
---------------- HELP ------------------
newcpp new {PROJECT_NAME} [CPP_VERSION]
PROJECT_NAME - string name of the project i.e. MyProject
CPP_VERSION (OPTIONAL, DEFAULT 17) - int version of CPP compiler i.e. 20
Example: newcpp new MyProject 23
----------------------------------------
```

## Building a generated project

Once a project has been generated, build and run it with the included script:

```powershell
cd MyProject
./run.ps1
```

## Project structure

```
.
├── src/
│   ├── main.cpp          # Entry point: parses CLI arguments
│   ├── template.cpp/.hpp # Reads template files and generates the new project
│   ├── constants.hpp     # CLI messages, flags, and template file paths
│   └── types.hpp         # Shared enums/structs (Action, Flag, Data)
├── templates/
│   ├── MainTemplate.txt
│   ├── CMakeTemplate.txt
│   └── BuildScriptTemplate.txt
└── CMakeLists.txt
```

## License

Licensed under the [GNU General Public License v3.0](LICENSE).
