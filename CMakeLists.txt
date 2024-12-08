cmake_minimum_required(VERSION 3.27)
project(op_game)

set(CMAKE_CXX_STANDARD 17)

add_executable(
        op_game src/main.cpp
        src/player.cpp
        )
