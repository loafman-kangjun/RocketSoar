cmake_minimum_required(VERSION 3.16)
project(RocketSoar)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

find_package(SDL3 CONFIG REQUIRED)
find_package(SDL3_ttf CONFIG REQUIRED)

# Create your game executable target as usual
add_executable(RocketSoar main.cpp)

# Link to the actual SDL3 library.
target_link_libraries(RocketSoar PRIVATE
        SDL3::SDL3
        SDL3_ttf::SDL3_ttf
)

