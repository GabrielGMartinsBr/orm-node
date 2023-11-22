cmake_minimum_required(VERSION 3.5.0)
project(ORM-Core VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

include_directories(include)
include_directories(src)

# Debug
include(CTest)
enable_testing()

# Source Files
file(GLOB_RECURSE source_files src/*.cpp src/*.hpp)

# CPack 
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

set(CoreLib "${PROJECT_NAME}")


# Executable
# add_executable(${PROJECT_NAME} ${source_files})


# # Ruby
# find_package(RubyStatic REQUIRED)
# include_directories(${RubyStatic_INCLUDE_DIRS})
# target_link_libraries(${PROJECT_NAME} ${RubyStatic_LIBRARIES} -lcrypt)


# # Boost Filesystem
# find_package(Boost COMPONENTS system filesystem REQUIRED)
# target_link_libraries(${PROJECT_NAME}  
#   ${Boost_FILESYSTEM_LIBRARY}
#   ${Boost_SYSTEM_LIBRARY}
# )



# Create the library
add_library(${CoreLib} STATIC src/core/Reader.cpp)


# Ruby
find_package(Ruby REQUIRED)
include_directories(${Ruby_INCLUDE_DIRS})
target_link_libraries(${CoreLib}
  ${Ruby_LIBRARIES}
)


# Boost Filesystem
find_package(Boost REQUIRED COMPONENTS system filesystem)
target_link_libraries(${CoreLib}
  Boost::boost
  Boost::atomic
  Boost::system
  Boost::filesystem
)

set_target_properties(${CoreLib} PROPERTIES POSITION_INDEPENDENT_CODE ON)
