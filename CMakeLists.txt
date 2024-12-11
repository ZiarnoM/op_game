cmake_minimum_required(VERSION 3.27)
project(op_game)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

file(GLOB SOURCES "src/*.cpp")
add_executable(op_game ${SOURCES}
        src/LevelLoader.cpp
        include/LevelLoader.h
        src/StartMenu.cpp
        include/StartMenu.h)

target_link_libraries(op_game sfml-system sfml-window sfml-graphics)