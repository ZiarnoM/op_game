cmake_minimum_required(VERSION 3.27)
project(op_game)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

file(GLOB SOURCES "src/*.cpp")
add_executable(op_game ${SOURCES})

target_link_libraries(op_game sfml-system sfml-window sfml-graphics)

# Enable testing
enable_testing()

# Add testing framework (Catch2)
find_package(Catch2 REQUIRED) # Ensure Catch2 is installed via vcpkg or other means

# Add a target for unit tests
add_executable(op_game_tests
    tests/unit_tests.cpp
    src/player.cpp
)
target_link_libraries(op_game_tests
    sfml-system
    sfml-window
    sfml-graphics
    Catch2::Catch2
)

# Register the tests with CTest
add_test(NAME op_game_tests COMMAND op_game_tests)