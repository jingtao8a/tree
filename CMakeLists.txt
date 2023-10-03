cmake_minimum_required(VERSION 3.13)
project("tree")

set(CMAKE_CXX_FLAGS "-std=c++14 -g")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(src/old)
add_subdirectory(test)