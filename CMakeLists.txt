cmake_minimum_required(VERSION 3.22)
project(imgui_test)

set(CMAKE_CXX_STANDARD 20)

# SFML libraries
# set(SFML_STATIC_LIBRARIES TRUE)
set(EXTERNAL_SFML TRUE)
set(SFML_LIBS sfml-window sfml-graphics sfml-system)
find_package(SFML 2.5 COMPONENTS window graphics system REQUIRED)

# SPDLOG
find_package(spdlog REQUIRED)

# FMT
find_package(fmt REQUIRED)

# IMGUI
find_package(OpenGL REQUIRED) # imgui-sfml depends on opengl 
set(IMGUI_DIR depends/imgui)
set(IMGUI_SFML_DIR depends/imgui-sfml)
set(IMGUI_SRC ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_tables.cpp ${IMGUI_DIR}/imgui_widgets.cpp ${IMGUI_SFML_DIR}/imgui-SFML.cpp)

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
        Framework/Color.hpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(imgui_test
        ${APPLICATION_INCLUDE}
        ${IMGUI_DIR}
        ${IMGUI_SFML_DIR}
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
