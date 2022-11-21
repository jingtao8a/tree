cmake_minimum_required(VERSION 3.18)
project("duckdb_study")

add_executable(avl_tree src/avl_tree.cpp)

add_executable(binary_search_tree src/binaray_search_tree.cpp)

add_executable(create_btree src/create_btree.cpp)

add_executable(rb_tree src/rb_tree.cpp)

add_executable(red_black src/red_black.cpp)

set(CMAKE_CXX_FLAGS "-std=c++11 -g")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)