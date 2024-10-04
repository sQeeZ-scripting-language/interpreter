# CMake Configuration for sQeeZ-Interpreter
cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the project name
project(sQeeZ-Interpreter)

# OS specific configurations
if(MSVC)
  add_definitions(-D_SQEEZ_WIN)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
elseif(APPLE)
  add_definitions(-D_SQEEZ_MAC)
else()
  add_definitions(-D_SQEEZ_LINUX)
endif()

# Include the header directory
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Include Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# Configure Google Test
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()
include(GoogleTest)

# Include the source files
file(GLOB_RECURSE SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

# Include the header files
file(GLOB_RECURSE HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

# Create the Library
add_library(
  sQeeZ-Interpreter-Lib 
  STATIC 
  ${SOURCES} 
  ${HEADERS}
)

# Create the Executable
add_executable(
  sQeeZ-Interpreter-Exe
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)
target_link_libraries(
  sQeeZ-Interpreter-Exe 
  sQeeZ-Interpreter-Lib
)

# Interpreter Test
add_executable(
  interpreter_test 
  ${CMAKE_CURRENT_SOURCE_DIR}/test/interpreter_test.cc
)
target_link_libraries(
  interpreter_test 
  GTest::gtest_main
  sQeeZ-Interpreter-Lib
)
gtest_discover_tests(interpreter_test)
