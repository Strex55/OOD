cmake_minimum_required(VERSION 3.15)
project(GeometryFactory)

set(CMAKE_CXX_STANDARD 17)

# УБРАН ПОИСК SFML - ВСЯ ЭТА СТРОКА УДАЛЕНА

# Поиск Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Основное приложение
add_executable(GeometryFactory
    main.cpp
    ShapeFactory.cpp
    FileShapeParser.cpp
    Functions.cpp
    CPoint.cpp
    CLineSegment.cpp
    CTriangle.cpp
    CRectangle.cpp
    CCircle.cpp
)

# Тестовое приложение
add_executable(GeometryFactoryTests
    test.cpp
    ShapeFactory.cpp
    FileShapeParser.cpp
    Functions.cpp
    CPoint.cpp
    CLineSegment.cpp
    CTriangle.cpp
    CRectangle.cpp
    CCircle.cpp
)

# УБРАНА ССЫЛКА НА SFML - ЭТИ СТРОКИ УДАЛЕНЫ

# Подключение Google Test к тестовому приложению
target_link_libraries(GeometryFactoryTests PRIVATE gtest gtest_main)

# Настройки include директорий
target_include_directories(GeometryFactory PRIVATE .)
target_include_directories(GeometryFactoryTests PRIVATE .)

# УБРАН БЛОК КОПИРОВАНИЯ DLL - ЭТОТ БЛОК УДАЛЕН

# Добавляем тесты
enable_testing()
add_test(NAME GeometryFactoryTests COMMAND GeometryFactoryTests)