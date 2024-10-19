# CMake Configuration for sQeeZ-Interpreter
cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=1)

# Set the project name
project(sQeeZ-Interpreter)

# OS specific configurations
if(MSVC)
  message(FATAL_ERROR "MSVC is not supported")
elseif(CMAKE_C_COMPILER_ID STREQUAL "GNU")
  add_definitions(-D_SQEEZ_WIN)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
elseif(APPLE)
  add_definitions(-D_SQEEZ_MAC)
  set(CMAKE_OSX_ARCHITECTURES "arm64")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -arch arm64")
else()
  add_definitions(-D_SQEEZ_LINUX)
endif()

# Print the compiler information
message(STATUS "Operating System: ${CMAKE_SYSTEM_NAME}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "C Compiler Version: ${CMAKE_C_COMPILER_VERSION}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")

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
  ${CMAKE_CURRENT_SOURCE_DIR}/src/interpreter/*.cpp
)

# Include the header files
file(GLOB_RECURSE HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/interpreter/*.hpp
)

# Include the Lexer
set(SQEEZ_LEXER_LIB_PATH ${CMAKE_SOURCE_DIR}/lexer-lib/libsQeeZ-Lexer-Lib.a)
set(SQEEZ_LEXER_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/lexer)
include_directories(${SQEEZ_LEXER_INCLUDE_DIR})
add_library(sQeeZ-Lexer-Lib STATIC IMPORTED)
set_target_properties(sQeeZ-Lexer-Lib PROPERTIES IMPORTED_LOCATION ${SQEEZ_LEXER_LIB_PATH})

#Include the Parser
set(SQEEZ_PARSER_LIB_PATH ${CMAKE_SOURCE_DIR}/parser-lib/libsQeeZ-Parser-Lib.a)
set(SQEEZ_PARSER_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/parser)
include_directories(${SQEEZ_PARSER_INCLUDE_DIR})
add_library(sQeeZ-Parser-Lib STATIC IMPORTED)
set_target_properties(sQeeZ-Parser-Lib PROPERTIES IMPORTED_LOCATION ${SQEEZ_PARSER_LIB_PATH})

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
  sQeeZ-Lexer-Lib
  sQeeZ-Parser-Lib
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
  sQeeZ-Lexer-Lib
  sQeeZ-Parser-Lib
)
gtest_discover_tests(interpreter_test)
