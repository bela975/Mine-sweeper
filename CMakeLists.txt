cmake_minimum_required(VERSION 3.25)
project(untitled9)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled9 SourceFiles/Main.cpp SourceFiles/Square.cpp SourceFiles/GetSquare.cpp SourceFiles/CreateText.cpp SourceFiles/Board.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH})
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/MINGW/SFML/SFML-2.5.1/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(C:/MINGW/SFML/include/SFML)
target_link_libraries(untitled9 sfml-system sfml-window sfml-graphics sfml-audio)



