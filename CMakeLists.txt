cmake_minimum_required(VERSION 3.27)
project(op_game)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(
        op_game src/main.cpp
        src/player.cpp
        )

target_link_libraries(op_game sfml-system sfml-window sfml-graphics)