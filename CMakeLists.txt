cmake_minimum_required(VERSION 3.20)
project(swaw_app C CXX ASM)

add_subdirectory(${BSP_DIR})

add_executable(swaw_app app.cpp)

target_link_libraries(swaw_app bsp)
