cmake_minimum_required(VERSION 3.10)
project(DFlat C)

set(CMAKE_C_STANDARD 99)

file(GLOB_RECURSE DFLAT_SOURCES "src/core/*.c")
file(GLOB_RECURSE DFLAT_HEADERS "include/dflat/*.h")


add_library(dflat ${DFLAT_SOURCES} ${DFLAT_HEADERS})
target_include_directories(dflat PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(demo examples/demo.c)
target_link_libraries(demo PRIVATE dflat)
