cmake_minimum_required(VERSION 3.5.0)
project(ORM-Core VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

# Debug
include(CTest)
enable_testing()

# CPack 
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

find_package(Boost REQUIRED COMPONENTS system filesystem)
find_package(Ruby REQUIRED)



#--------------------------------------------------------------
# ORM/Core Lib
#
set(CoreLib "${PROJECT_NAME}-LIB")
add_library(
  ${CoreLib} STATIC
  ${CMAKE_SOURCE_DIR}/public/src/orm-core.cpp
)

target_include_directories(
  ${CoreLib} PRIVATE
  ${CMAKE_SOURCE_DIR}/common
  ${CMAKE_SOURCE_DIR}/public/include
  ${CMAKE_SOURCE_DIR}/private/include
  ${CMAKE_SOURCE_DIR}/private/src
)

# Ruby
target_include_directories(
  ${CoreLib} PRIVATE
  ${Ruby_INCLUDE_DIRS}
)
target_link_libraries(${CoreLib}
  ${Ruby_LIBRARIES}
)

# Boost
target_include_directories(
  ${CoreLib} PRIVATE
  ${Boost_INCLUDE_DIRS}
)
target_link_libraries(${CoreLib}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)

set_target_properties(${CoreLib} PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(${CoreLib} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})



#--------------------------------------------------------------
# ORM Dev App(Executable)
# 
set(CoreDevApp "${PROJECT_NAME}-DEV-APP")

# Source Files
file(GLOB_RECURSE source_files 
  ${CMAKE_SOURCE_DIR}/private/src/*.cpp
  ${CMAKE_SOURCE_DIR}/private/src/*.hpp
  ${CMAKE_SOURCE_DIR}/public/src/*.cpp
  ${CMAKE_SOURCE_DIR}/public/src/*.hpp
)
add_executable(${CoreDevApp} ${source_files})

target_include_directories(
  ${CoreDevApp} PRIVATE
  ${CMAKE_SOURCE_DIR}/common
  ${CMAKE_SOURCE_DIR}/public/include
  ${CMAKE_SOURCE_DIR}/private/include
  ${CMAKE_SOURCE_DIR}/private/src
)

# Ruby
target_include_directories(
  ${CoreDevApp} PRIVATE
  ${Ruby_INCLUDE_DIRS}
)
target_link_libraries(${CoreDevApp}
  ${Ruby_LIBRARIES}
)

# Boost
target_include_directories(
  ${CoreDevApp} PRIVATE
  ${Boost_INCLUDE_DIRS}
)
target_link_libraries(${CoreDevApp}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
)

set_target_properties(${CoreDevApp} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})