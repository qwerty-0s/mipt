cmake_minimum_required(VERSION 3.10)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--no-warn-rwx-segments")

find_package(FLTK REQUIRED)

add_executable(snake_game 
    main.cpp  
    snakeBack.cpp
)

target_link_libraries(snake_game 
    ${FLTK_LIBRARIES}
)


add_executable(snake_tests 
    test_snakeBack.cpp
    snakeBack.cpp
)

# Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.tar.gz
)
FetchContent_MakeAvailable(googletest)

target_link_libraries(snake_tests
    gtest_main
    gmock
)

enable_testing()
add_test(NAME SnakeTests COMMAND snake_tests)