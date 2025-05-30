cmake_minimum_required(VERSION 3.14)
project(paulidecomp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create library
add_library(paulidecomp INTERFACE)
target_include_directories(paulidecomp INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)