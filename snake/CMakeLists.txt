cmake_minimum_required(VERSION 3.10)
project(SnakeFLTK)

set(CMAKE_CXX_STANDARD 17)


set(SOURCES
    main.cpp
    snakeBack.cpp
    snakeGraph.cpp
)


find_package(FLTK REQUIRED NO_MODULE)


add_executable(SnakeFLTK ${SOURCES})


target_link_libraries(SnakeFLTK PRIVATE fltk fltk_images)
target_include_directories(SnakeFLTK PRIVATE ${FLTK_INCLUDE_DIR})
# Define USE_FLTK for sources that rely on FLTK (so tests can build without FLTK)
target_compile_definitions(SnakeFLTK PRIVATE USE_FLTK)