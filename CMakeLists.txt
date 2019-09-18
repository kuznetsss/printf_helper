cmake_minimum_required(VERSION 3.12)
project(test_project)

set(CMAKE_CXX_STANDARD 17)

add_library(printf_helper INTERFACE)
target_include_directories(printf_helper INTERFACE include)

add_executable(printf_helper_test test.cpp)
target_link_libraries(printf_helper_test PRIVATE printf_helper)
