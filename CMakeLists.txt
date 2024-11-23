cmake_minimum_required(VERSION 3.29)
project(FSignal)

set(CMAKE_CXX_STANDARD 17)

include_directories(
        godot-cpp/include/
        godot-cpp/gdextension/
        godot-cpp/gen/include/
)

add_library(FSignal SHARED
        src/FSignal/FSignal.cpp
        src/FSignal/FSignal.h
        src/register_types.cpp
        src/register_types.h

)
