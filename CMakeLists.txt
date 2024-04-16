cmake_minimum_required(VERSION 3.20)
project(test_main)

set(CMAKE_CXX_STANDARD 20)

# 将所有 src/*.cpp 文件列出来
file(GLOB_RECURSE CXX_SOURCE ${PROJECT_SOURCE_DIR}/src/*.cpp)

# 这里 SOURCE 表示所有用于编译成内置函数库的 cpp 文件
set(SOURCE ${CXX_SOURCE}
        src/rb_tree.cpp
        src/bit.cpp
        src/dp_pre.cpp
        src/enum.cpp
        src/tarjan.cpp)

#获取所有资源文件
#file(GLOB_RECURSE RESOURCE_FILE ${PROJECT_SOURCE_DIR}/resource/*.*)

add_executable(test_main ${SOURCE})
