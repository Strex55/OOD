cmake_minimum_required(VERSION 3.15)
project(GeomVisualizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем vcpkg toolchain
set(CMAKE_TOOLCHAIN_FILE "D:/Nikita/3_COURSE/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Ищем SFML 2.5
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

# Список всех исходных файлов
set(SOURCE_FILES
    src/Geometry.cpp
    src/Parser.cpp
    src/ShapeAdapter.cpp
    src/TriangleAdapter.cpp
    src/RectangleAdapter.cpp
    src/CircleAdapter.cpp
    src/CompositeShape.cpp
    src/SelectionManager.cpp
    src/DragAndDrop.cpp
    src/CompositeManager.cpp
    src/App.cpp
)

# Список всех заголовочных файлов
set(HEADER_FILES
    include/Geometry.h
    include/Parser.h
    include/ShapeAdapter.h
    include/TriangleAdapter.h
    include/RectangleAdapter.h
    include/CircleAdapter.h
    include/CompositeShape.h
    include/SelectionManager.h
    include/DragAnddrop.h
    include/CompositeManager.h
    include/App.h
)

# Основная библиотека
add_library(geom_core STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(geom_core PUBLIC include)
target_link_libraries(geom_core PUBLIC sfml-graphics sfml-window sfml-system)

# Исполняемый файл
add_executable(geom_app src/main.cpp)
target_link_libraries(geom_app PRIVATE geom_core)

# Предупреждения компилятора
if(MSVC)
    target_compile_options(geom_core PRIVATE /W4 /permissive-)
    target_compile_options(geom_app PRIVATE /W4 /permissive-)
endif()