cmake_minimum_required(VERSION 3.12)
project(printf_helper)

if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.14/conan.cmake"
    "${CMAKE_BINARY_DIR}/conan.cmake")
endif ()


include(${CMAKE_BINARY_DIR}/conan.cmake)
set(ENV{CONAN_USER_HOME} ${PROJECT_SOURCE_DIR})
if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
  set(CONAN_COMPILER gcc)
else ()
  set(CONAN_COMPILER clang)
endif ()
string(SUBSTRING ${CMAKE_CXX_COMPILER_VERSION} 0 1 CONAN_COMPILER_VERSION)

conan_cmake_run(REQUIRES gtest/1.8.1
  BASIC_SETUP CMAKE_TARGETS
  BUILD missing
  SETTINGS compiler=${CONAN_COMPILER}
  compiler.version=${CONAN_COMPILER_VERSION}
  ENV CC=${CMAKE_C_COMPILER}
  CXX=${CMAKE_CXX_COMPILER}
  )

set(CMAKE_CXX_STANDARD 17)

add_library(printf_helper INTERFACE)
target_include_directories(printf_helper INTERFACE include)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ TYPE INCLUDE)

add_executable(printf_helper_tests tests/printf_helper_tests.cpp)
target_link_libraries(printf_helper_tests
  PRIVATE
  printf_helper
  CONAN_PKG::gtest
  )

add_test(COMMAND printf_helper_tests NAME printf_helper_tests)