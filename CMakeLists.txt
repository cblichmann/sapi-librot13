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

# Set this on the command-line
set(SAPI_ROOT "" CACHE PATH "Path to the Sandboxed API source tree")
# To obtain a full SAPI_ROOT check out its source separately:
#   git clone https://github.com/google/sandboxed-api.git $HOME/sapi_root
# Then configure:
#   mkdir -p build && cd build
#   cmake .. -G Ninja -DSAPI_ROOT=$HOME/sapi_root

set(SAPI_ENABLE_EXAMPLES OFF CACHE BOOL "")
set(SAPI_ENABLE_TESTS OFF CACHE BOOL "")
add_subdirectory("${SAPI_ROOT}"
                 "${CMAKE_BINARY_DIR}/sandboxed-api-build"
                 # Omit this to have the full Sandboxed API in IDE
                 EXCLUDE_FROM_ALL)

add_sapi_library(rot13_sapi
  FUNCTIONS Rot13File  # List of functions that we want to include in the
                       # generated sandboxed API class
  INPUTS rot13.h       # Header files or .cc files that should be parsed
  LIBRARY rot13        # Library dependency from the add_library() above
  LIBRARY_NAME Rot13   # Name prefix for the generated header. Will be
                       # suffixed with "Api" and "Sandbox" as needed.
  NAMESPACE ""         # Optional C++ namespace to wrap the generated code
)
target_include_directories(rot13_sapi INTERFACE
  "${PROJECT_BINARY_DIR}"  # To find the generated SAPI header
)

add_executable(rot13_sandboxed
  main_sandboxed.cc
)
target_link_libraries(rot13_sandboxed PRIVATE
  rot13_sapi
  sapi::sapi
)
