cmake_minimum_required(VERSION 3.29)
project(AoC2024)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE HEADER_FILES src/*.hpp)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

add_custom_target(copy_input ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/src/input
    ${CMAKE_CURRENT_BINARY_DIR}/input
    COMMENT "Copying input files..."
)
add_dependencies(${PROJECT_NAME} copy_input)