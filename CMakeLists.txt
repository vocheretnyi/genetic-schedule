cmake_minimum_required(VERSION 3.15)
project(genetic_schedule)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(genetic_schedule
        CMakeLists.txt
        DNA.h
        main.cpp
        Population.cpp
        Population.h)
