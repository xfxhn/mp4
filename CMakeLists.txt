cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(MP4 LANGUAGES CXX C)

option(USE_MYMATH "Use provided math implementation" ON)
#cpp11标准
set(CMAKE_CXX_STANDARD 11)
#关闭编译器扩展
set(CMAKE_CXX_EXTENSIONS OFF)
#指定必须要11标准，不然cmake会自己找
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)