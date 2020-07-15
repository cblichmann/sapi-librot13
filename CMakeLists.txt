cmake_minimum_required(VERSION 3.10)

project(rot13 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(rot13 STATIC
  rot13.h
  rot13.cc
)

add_executable(rot13_main
  main.cc
)
target_link_libraries(rot13_main PRIVATE
  rot13
)
