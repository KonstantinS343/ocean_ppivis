cmake_minimum_required(VERSION 3.23)
project(Ocean)

set(CMAKE_CXX_STANDARD 14)

add_executable(Ocean main.cpp liv/living.h liv/shark.cpp liv/salmon.cpp liv/corals.cpp liv/kril.cpp liv/seaweed.cpp liv/clown.cpp liv/anchovys.cpp liv/puffer.cpp oceanfield/ocean.cpp oceanfield/ocean.h system/ocean_system.cpp system/ocean_system.h error/error.h system/file.h)
