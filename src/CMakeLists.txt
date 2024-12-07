cmake_minimum_required(VERSION 3.30)
project(FSignal)

set(CMAKE_CXX_STANDARD 20)
add_compile_options("/utf-8")

if (NOT DEFINED OutputDir)
    message(FATAL_ERROR "请在根CMakeLists.txt中手动定义 OutputDir 变量")
endif ()


# 将可执行文件生成到bin目录，静态库文件生成到lib目录
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OutputDir}/bin/debug)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OutputDir}/lib/debug)
elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OutputDir}/bin/release)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OutputDir}/lib/release)
else ()
    message(FATAL_ERROR "没有对应的版本适配当前的构建类型...")
endif ()

# 将头文件递归复制到include目录
file(GLOB_RECURSE head_files "*.h" "*.hpp")
foreach (file ${head_files})
    file(RELATIVE_PATH file ${PROJECT_SOURCE_DIR} ${file})
    get_filename_component(file_dir ${file} DIRECTORY)
    file(COPY ${file} DESTINATION ${OutputDir}/include/${file_dir})
endforeach ()


add_library(
        ${PROJECT_NAME} SHARED register_types.cpp
        FSignal/FSlot.cpp
        FSignal/FSignal.cpp
)
find_package(unofficial-godot-cpp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::godot::cpp)

add_library(
        ${PROJECT_NAME}-static STATIC register_types.cpp
        FSignal/FSlot.cpp
        FSignal/FSignal.cpp
)
find_package(unofficial-godot-cpp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}-static PRIVATE unofficial::godot::cpp)
