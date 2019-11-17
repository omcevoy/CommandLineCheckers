cmake_minimum_required(VERSION 3.12)
project(game)

set(CMAKE_CXX_STANDARD 14)

add_executable(Checkers main.cc heads/Tree.h heads/Score.h Score.cc heads/Board.h Board.cc heads/Tile.h Tile.cc heads/CLI.h CLI.cc )
