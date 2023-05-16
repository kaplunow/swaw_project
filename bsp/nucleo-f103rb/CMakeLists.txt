
add_library(bsp STATIC src/bsp.cpp)
target_include_directories(bsp PUBLIC include)

include(FetchContent)
FetchContent_Declare( 
    jlink_rtt
    GIT_REPOSITORY https://github.com/jmacheta/jlink_rtt-cmake
    GIT_TAG main
)
FetchContent_MakeAvailable(jlink_rtt)
target_link_libraries(bsp PUBLIC jlink_rtt)

FetchContent_Declare(
    cubemx_cmake
    GIT_REPOSITORY https://github.com/jmacheta/cubemx-cmake.git
    GIT_TAG main
)
FetchContent_MakeAvailable(cubemx_cmake)
cubemx_add_library(swaw)
target_link_libraries(bsp PUBLIC swaw)
