cmake_minimum_required(VERSION 3.18)
project("duckdb_study")

add_executable(avl_tree src/old/avl_tree.cpp)

add_executable(binary_search_tree src/old/binaray_search_tree.cpp)

add_executable(create_btree src/old/create_btree.cpp)

add_executable(rb_tree src/old/rb_tree.cpp)

add_executable(red_black src/old/red_black.cpp)

add_executable(testqueue test/testqueue.cpp)

add_executable(testbst test/testbst.cpp src/binary_search_tree.cpp)

add_executable(geoperation test/geoperation.cpp)

add_executable(testavl test/testavl.cpp src/avl_tree.cpp)

set(CMAKE_CXX_FLAGS "-std=c++11 -g")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)