cmake_minimum_required(VERSION 3.22)
project(imgui_test)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

include_directories(imgui_test ${SDL2_INCLUDE_DIRS} imgui)

add_executable(imgui_test main.cpp logging/ConsoleLogger.cpp logging/FileLogger.cpp logging/FileLogger.hpp logging/Logger.cpp)
target_link_libraries(imgui_test ${SDL2_LIBRARIES} fmt spdlog)
