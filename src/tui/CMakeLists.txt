cmake_minimum_required(VERSION 3.30)
project(LaTeX-tui VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Curses REQUIRED)

add_executable(driver main.cpp window_manager.cpp)

target_include_directories(driver PRIVATE ${CURSES_INCLUDE_DIRS})
target_compile_options(driver PRIVATE -Wall -march=native)
target_link_libraries(driver PRIVATE ${CURSES_LIBRARIES})
