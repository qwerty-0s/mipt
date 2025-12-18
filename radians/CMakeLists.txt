cmake_minimum_required(VERSION 3.10)
project(radians)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(SOURCES
    radians.cpp
    main.cpp
)

add_executable(angle_test ${SOURCES})
