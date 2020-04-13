cmake_minimum_required(VERSION 3.15)
project(genetic_schedule)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(genetic_schedule
        main.cpp
        Population.cpp
        Classes.cpp)
