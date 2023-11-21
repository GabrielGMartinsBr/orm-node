cmake_minimum_required(VERSION 3.5.0)
project(ORM-Core VERSION 0.1.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_STANDARD 11)

# Debug
include(CTest)
enable_testing()

# Source Files
file(GLOB_RECURSE source_files src/*.cpp src/*.hpp)

include_directories(src)

# CPack 
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Executable
add_executable(${PROJECT_NAME} ${source_files})