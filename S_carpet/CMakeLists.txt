cmake_minimum_required(VERSION 3.20)
project(S_carpet LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-Wall -Wextra -g)
else()
    add_compile_options(-Wall -Wextra -O2)
endif()

set(HEADERS
    SierpinskyWidget.h
)

set(SOURCES
    main.cpp
)

set(FLTK_SKIP_FLUID TRUE)
set(FLTK_SKIP_FORMS TRUE)

find_package(FLTK 1.3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(
    ${FLTK_INCLUDE_DIR}
)


add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)



target_link_libraries(${PROJECT_NAME}
    ${FLTK_LIBRARIES}
    ${OPENGL_LIBRARIES}
    jpeg
    png
    z
    X11
)


install(TARGETS ${PROJECT_NAME} DESTINATION bin)


add_custom_target(run
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Запуск приложения ${PROJECT_NAME}"
)
