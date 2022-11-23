cmake_minimum_required(VERSION 3.18)
project("duckdb_study")

add_executable(avl_tree test/avl_tree.cpp)

add_executable(binary_search_tree test/binaray_search_tree.cpp)

add_executable(create_btree test/create_btree.cpp)

add_executable(rb_tree test/rb_tree.cpp)

add_executable(red_black test/red_black.cpp)

add_executable(testqueue test/testqueue.cpp)

add_executable(testbst test/testbst.cpp src/binary_search_tree.cpp)

add_executable(geoperation test/geoperation.cpp)

set(CMAKE_CXX_FLAGS "-std=c++11 -g")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)