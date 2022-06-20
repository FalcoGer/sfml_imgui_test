cmake_minimum_required(VERSION 3.22)
project(imgui_test)

set(CMAKE_CXX_STANDARD 20)

# SFML libraries
# set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS window graphics system REQUIRED)
set(SFML_LIBS sfml-window sfml-graphics sfml-system)

find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

set(IMGUI_DIR imgui)

include_directories(imgui_test ${IMGUI_DIR})
add_executable(imgui_test main.cpp logging/ConsoleLogger.cpp logging/FileLogger.cpp logging/FileLogger.hpp logging/Logger.cpp Framework/Framework.cpp Framework/Framework.hpp Framework/Application.hpp MyApplication.cpp MyApplication.hpp)
target_link_libraries(imgui_test fmt spdlog ${SFML_LIBS})
