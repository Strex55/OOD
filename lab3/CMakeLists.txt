cmake_minimum_required(VERSION 3.20)
project(GeomVisualizer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
option(BUILD_VISUALIZATION "Enable SFML window visualization" ON)

# Find SFML (recommend using vcpkg or system package)
if(BUILD_VISUALIZATION)
  # Try SFML 3 (CONFIG mode via Homebrew/vcpkg) first
  find_package(SFML CONFIG QUIET COMPONENTS Graphics Window System)
  if(NOT SFML_FOUND)
    # Fallback to SFML 2.5 (module mode)
    find_package(SFML 2.5 QUIET COMPONENTS graphics window system)
  endif()
  if(NOT SFML_FOUND)
    message(FATAL_ERROR "SFML not found. Install SFML 3 (brew install sfml) or SFML 2.5 (vcpkg install sfml).")
  endif()
endif()

add_library(geom_core
  src/Geometry.cpp
  src/Parser.cpp
  src/ShapeAdapter.cpp
  src/TriangleAdapter.cpp
  src/RectangleAdapter.cpp
  src/CircleAdapter.cpp
  src/CompositeShape.cpp
  src/Application.cpp
  src/StateFactory.cpp
  src/SelectState.cpp
  src/FillState.cpp
  src/AddShapeState.cpp
  src/Toolbar.cpp
  src/MoveCommand.cpp
  src/GroupCommand.cpp
  src/DragAndDrop.cpp
  src/SelectionManager.cpp
  src/CompositeManager.cpp
)

target_include_directories(geom_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
if(BUILD_VISUALIZATION)
  # Link to proper SFML targets depending on version
  if(TARGET SFML::Graphics)
    # SFML 3.x target names
    target_link_libraries(geom_core PUBLIC SFML::Graphics SFML::Window SFML::System)
  elseif(TARGET sfml-graphics)
    # SFML 2.x target names
    target_link_libraries(geom_core PUBLIC sfml-graphics sfml-window sfml-system)
  else()
    message(FATAL_ERROR "SFML targets not found after find_package.")
  endif()
endif()

add_executable(geom_app src/main.cpp)
target_link_libraries(geom_app PRIVATE geom_core)

if(MSVC)
  target_compile_options(geom_core PRIVATE /W4 /permissive-)
  target_compile_options(geom_app PRIVATE /W4 /permissive-)
else()
  target_compile_options(geom_core PRIVATE -Wall -Wextra -Wpedantic)
  target_compile_options(geom_app PRIVATE -Wall -Wextra -Wpedantic)
endif()


