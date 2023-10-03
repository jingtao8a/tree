set(GOOGLETEST_ROOT third_party/googletest/googletest CACHE STRING "Google Test source root")

# SYSTEM表示当前头文件搜索路径只在当前文件有效
include_directories(SYSTEM 
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/include)

set(GOOGLETEST_SOURCES
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest-all.cc
        ${PROJECT_SOURCE_DIR}/${GOOGLETEST_ROOT}/src/gtest_main.cc
        )

foreach(_source ${GOOGLETEST_SOURCES})
    set_source_files_properties(${_source} PROPERTIES GENERATED 1)
endforeach()

add_library(gtest STATIC ${GOOGLETEST_SOURCES})
target_link_libraries(gtest pthread)

add_executable(testqueue testqueue.cpp)

add_executable(testbst testbst.cpp ../src/binary_search_tree.cpp)

add_executable(geoperation geoperation.cpp)

add_executable(testavl testavl.cpp ../src/avl_tree.cpp)

add_executable(testradix testradix.cpp ../src/radix_tree.cpp)
target_link_libraries(testradix gtest)