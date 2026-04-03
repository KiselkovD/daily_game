# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

project(daily_game LANGUAGES CXX)

# Версия C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Собираем исполняемый файл из main.cpp и всех src/**/*.cpp
file(
  GLOB_RECURSE
  SOURCES
  "src/*.cpp"
  "src/core/*.cpp"
  "src/games/**/*.cpp"
)

add_executable(${PROJECT_NAME}
  "src/main.cpp"
  ${SOURCES}
)

# Подключаем include/ так, чтобы писать #include "game.hpp" и т.п.
target_include_directories(${PROJECT_NAME}
  PRIVATE
  "include"
)