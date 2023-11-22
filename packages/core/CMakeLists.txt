cmake_minimum_required(VERSION 3.5.0)
project(ORM-Core VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_HOME_DIRECTORY ./)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

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

# find_package(RubyStatic REQUIRED)
# include_directories(${RubyStatic_INCLUDE_DIRS})
# link_libraries(
#   ${RubyStatic_LIBRARIES}
#   -lcrypt
# )


# # Executable
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

include_directories(include)


# Create the library
add_library(${PROJECT_NAME} STATIC src/core/Reader.cpp)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Ruby
find_package(Ruby REQUIRED)
include_directories(${Ruby_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME}
  ${Ruby_LIBRARIES}
  # -lcrypt
)


# Boost Filesystem
find_package(Boost REQUIRED COMPONENTS system filesystem)
target_link_libraries(${PROJECT_NAME}
  Boost::boost
  Boost::atomic
  Boost::system
  Boost::filesystem
)


set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
