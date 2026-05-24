cmake_minimum_required(VERSION 3.20)

project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Important for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# define the executable
add_executable(atp
    src/main.cpp
    src/terms.cpp
)
target_include_directories(atp PRIVATE
    include
)