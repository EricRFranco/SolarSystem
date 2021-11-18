cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

project(SOLAR_SYSTEM LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(solar_system
    src/main.cpp
)

set_target_properties(solar_system
PROPERTIES CXX_STANDARD 17
           CXX_STANDARD_REQUIRED ON
)

find_package(SDL2 REQUIRED)

target_include_directories(solar_system PRIVATE include ${SDL2_INCLUDE_DIRS})

target_link_libraries(solar_system
PRIVATE
  ${SDL2_LIBRARIES}
)