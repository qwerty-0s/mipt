cmake_minimum_required(VERSION 3.10)
project(SnakeGameTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--no-warn-rwx-segments")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

add_executable(snake_tests 
   test_snakeBack.cpp
    ../snakeBack.cpp    
)

## Link FLTK and required X11/system libraries (resolves undefined X* references)
target_link_libraries(snake_tests
    PRIVATE
    fltk
    X11
    Xext
    Xrender
    Xcursor
    Xrandr
    Xinerama
    Xft
    fontconfig
    freetype
    dl
    pthread
)

# Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.tar.gz
)
FetchContent_MakeAvailable(googletest)

target_link_libraries(snake_tests
    PRIVATE
    gtest
    gtest_main
    gmock
    pthread
)

enable_testing()
add_test(NAME SnakeTests COMMAND snake_tests)