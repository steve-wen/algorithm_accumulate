cmake_minimum_required(VERSION 3.20)
project(test_main)

set(CMAKE_CXX_STANDARD 20)

add_executable(test_main src/main.cpp
        src/trie.cpp
        src/trie01.cpp
        src/segment_tree.cpp
        src/monotone_stack.cpp
        src/math_comb.cpp
        src/dp.cpp)
