cmake_minimum_required(VERSION 3.12)
project(printf_helper)

#if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#  conan_basic_setup(TARGETS)
#else()
#  message(WARNING "Can't find Conan file!")
#endif()

set(CMAKE_CXX_STANDARD 17)

add_library(printf_helper INTERFACE)
target_include_directories(printf_helper INTERFACE include)

add_executable(printf_helper_tests tests/printf_helper_tests.cpp)
target_link_libraries(printf_helper_tests
  PRIVATE
  printf_helper
  )
