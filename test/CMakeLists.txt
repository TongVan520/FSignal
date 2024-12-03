cmake_minimum_required(VERSION 3.30)
project(test)

set(CMAKE_CXX_STANDARD 20)
add_compile_options("/utf-8")

set(FSignal_ROOT ${PROJECT_SOURCE_DIR}/../)
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake)
find_package(FSignal REQUIRED)

add_library(${PROJECT_NAME} SHARED test.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE FSignal::FSignal)
