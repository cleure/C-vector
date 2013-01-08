cmake_minimum_required (VERSION 2.6)
project (vector)

set (CMAKE_C_FLAGS "-Wall --std=c89")

include_directories(
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_BINARY_DIR}"
    "./"
    "./include"
)

set(VECTOR_SOURCES
    src/vector.c
)

add_library(vector ${VECTOR_SOURCES})

add_executable(test1 tests/test1.c)
    
target_link_libraries(test1 vector)
