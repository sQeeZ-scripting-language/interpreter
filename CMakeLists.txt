cmake_minimum_required(VERSION 3.14)
project(interpreter)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)

add_executable(sQeeZ src/main.cpp)

target_link_libraries(sQeeZ src)

add_subdirectory(test)