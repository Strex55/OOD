cmake_minimum_required(VERSION 3.20)
project(GeomVisualizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find SFML 3.0 (config mode)
find_package(SFML CONFIG COMPONENTS Graphics Window System REQUIRED)

# Core library
add_library(geom_core
  src/Geometry.cpp
  src/Parser.cpp
  src/ShapeAdapter.cpp
  src/TriangleAdapter.cpp
  src/RectangleAdapter.cpp
  src/CircleAdapter.cpp
  src/App.cpp
)

target_include_directories(geom_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(geom_core PUBLIC SFML::Graphics SFML::Window SFML::System)

# Executable
add_executable(geom_app src/main.cpp)
target_link_libraries(geom_app PRIVATE geom_core)

# Compiler warnings
if(MSVC)
  target_compile_options(geom_core PRIVATE /W4 /permissive-)
  target_compile_options(geom_app PRIVATE /W4 /permissive-)
else()
  target_compile_options(geom_core PRIVATE -Wall -Wextra -Wpedantic)
  target_compile_options(geom_app PRIVATE -Wall -Wextra -Wpedantic)
endif()