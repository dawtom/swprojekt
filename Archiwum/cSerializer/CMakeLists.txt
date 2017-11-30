cmake_minimum_required(VERSION 3.8)
project(cSerializer)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c main.h)
add_executable(cSerializer ${SOURCE_FILES})