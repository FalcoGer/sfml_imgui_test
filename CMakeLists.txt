cmake_minimum_required(VERSION 3.22)
project(imgui_test)

set(CMAKE_CXX_STANDARD 20)

# SFML libraries
# set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS window graphics system REQUIRED)
find_package(OpenGL REQUIRED)
set(SFML_LIBS sfml-window sfml-graphics sfml-system)

find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

set(IMGUI_DIR imgui imgui-sfml)
set(IMGUI_SRC imgui/imgui.cpp imgui/imgui_demo.cpp imgui/imgui_draw.cpp imgui/imgui_tables.cpp imgui/imgui_widgets.cpp imgui-sfml/imgui-SFML.cpp)

set(APPLICATION_INCLUDE)
set(APPLICATION_SOURCE_FILES
        main.cpp
        logging/ConsoleLogger.cpp
        logging/FileLogger.cpp
        logging/FileLogger.hpp
        logging/Logger.cpp
        Framework/Framework.cpp
        Framework/Framework.hpp
        Framework/Application.hpp
        MyApplication.cpp
        MyApplication.hpp
        )

include_directories(imgui_test
        ${APPLICATION_INCLUDE}
        ${IMGUI_DIR}
        ${OPENGL_INCLUDE_DIRS}
        )

add_executable(imgui_test
        ${APPLICATION_SOURCE_FILES}
        ${IMGUI_SRC}
        )

target_link_libraries(imgui_test
        fmt
        spdlog
        ${SFML_LIBS}
        ${OPENGL_LIBRARIES}
        )
