cmake_minimum_required(VERSION 3.15)
project(untitled1 C)

set(CMAKE_C_STANDARD 11)

add_executable(CodeMatching main.c Hash/Hash.c Matching/Matching.c)