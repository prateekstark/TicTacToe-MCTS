cmake_minimum_required(VERSION 3.10)

# set the project name
project(TicTacToe VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-O3")

# add the executable
add_executable(TicTacToe TicTacToe.cpp 
						 MonteCarloTreeSearch.cpp
						 MonteCarloTreeSearch.h
						 Node.cpp
						 Node.h
						 utils.cpp
						 utils.h
				)