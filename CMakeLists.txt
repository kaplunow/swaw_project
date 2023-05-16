cmake_minimum_required(VERSION 3.20)
project(swaw_app C CXX ASM)

add_subdirectory(${BSP_DIR})

add_executable(swaw_app app.cpp)

set_target_properties(
    swaw_app 
    PROPERTIES 
        SUFFIX ".elf"
)

target_link_libraries(swaw_app PUBLIC bsp swaw)
