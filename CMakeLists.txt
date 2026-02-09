cmake_minimum_required(VERSION 4.0)
project(Football_league_manager)

set(CMAKE_CXX_STANDARD 20)

add_executable(Football_league_manager main.cpp
        teams.cpp
        teams.h)
