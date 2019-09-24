cmake_minimum_required(VERSION 3.12)
project(printf_helper)

if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.14/conan.cmake"
    "${CMAKE_BINARY_DIR}/conan.cmake")
endif ()


include(${CMAKE_BINARY_DIR}/conan.cmake)
set(ENV{CONAN_USER_HOME} ${CMAKE_BINARY_DIR}/../conan)
#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup(TARGETS)
conan_cmake_run(REQUIRES gtest/1.8.1
  BASIC_SETUP CMAKE_TARGETS
  BUILD missing)

set(CMAKE_CXX_STANDARD 17)

add_library(printf_helper INTERFACE)
target_include_directories(printf_helper INTERFACE include)

add_executable(printf_helper_tests tests/printf_helper_tests.cpp)
target_link_libraries(printf_helper_tests
  PRIVATE
  printf_helper
  CONAN_PKG::gtest
  )
