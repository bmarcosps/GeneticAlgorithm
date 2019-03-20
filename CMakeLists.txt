cmake_minimum_required(VERSION 3.13)
project(GeneticAlgorithm)

set(CMAKE_CXX_STANDARD 14)

add_executable(GeneticAlgorithm main.cpp constants.h Individual.cpp Individual.h Population.cpp Population.h Genetics.cpp Genetics.h Bitwise.cpp Bitwise.h)