cmake_minimum_required(VERSION 3.16)
project(control_lab CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cli adapters/cli_main.cpp)
target_include_directories(cli PRIVATE core)
