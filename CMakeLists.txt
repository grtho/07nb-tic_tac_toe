cmake_minimum_required(VERSION 3.23)
project(07nb_tic_tac_toe)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(07nb_tic_tac_toe
        main.cpp
        TTTGrid.cpp
        TTTGrid.hpp)
