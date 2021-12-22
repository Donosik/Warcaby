cmake_minimum_required(VERSION 3.16)
project(Warcaby)

set(CMAKE_CXX_STANDARD 23)

add_executable(Warcaby main.cpp Game.cpp Game.h Square.cpp Square.h Board.cpp Board.h Figure.cpp Figure.h NormalFigure.cpp NormalFigure.h QueenFigure.cpp QueenFigure.h Logic.cpp Logic.h)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(c:/SFML/include)
target_link_libraries(Warcaby sfml-system sfml-window sfml-graphics sfml-audio sfml-network)