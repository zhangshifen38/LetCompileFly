cmake_minimum_required(VERSION 3.22)
project(LetCompileFly)

set(CMAKE_CXX_STANDARD 17)

add_executable(LetCompileFly src/main.cpp Symboltable.h src/Quaternary.cpp src/Quaternary.h src/DAG.cpp src/DAG.h src/Token.cpp src/Token.h)
