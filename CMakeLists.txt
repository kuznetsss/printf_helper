cmake_minimum_required(VERSION 3.12)
project(test_project)

set(CMAKE_CXX_STANDART 17)

add_executable(test_project main.cpp)
#target_compile_options(test_project PUBLIC -stdlib=libc++)
