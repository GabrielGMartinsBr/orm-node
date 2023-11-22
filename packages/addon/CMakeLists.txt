cmake_minimum_required(VERSION 3.5.0)
cmake_policy(SET CMP0091 NEW)
cmake_policy(SET CMP0042 NEW)

project (orm-core-addon)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


add_definitions(-DNAPI_VERSION=8)


find_package(Boost REQUIRED COMPONENTS system filesystem)
find_package(Ruby REQUIRED)


include_directories(${CMAKE_JS_INC})
include_directories("/usr/include/")


file(GLOB SOURCE_FILES "src/addon.cpp")

add_library(
  ${PROJECT_NAME} SHARED 
  ${SOURCE_FILES} ${CMAKE_JS_SRC}
)

set_target_properties(
  ${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node"
)
target_link_libraries(
  ${PROJECT_NAME} ${CMAKE_JS_LIB}
)


# Lib ORM Core
target_include_directories(
  ${PROJECT_NAME} PRIVATE
  "${CMAKE_SOURCE_DIR}/../core/public/include/"
)

target_link_libraries(
  ${PROJECT_NAME} PRIVATE
  "${CMAKE_SOURCE_DIR}/../core/lib/libORM-Core.a"
)

# Lib Boost
target_link_libraries(
  ${PROJECT_NAME} PRIVATE
  Boost::system
  Boost::filesystem
)


# Lib Ruby
target_include_directories(
  ${PROJECT_NAME} PRIVATE
  ${Ruby_INCLUDE_DIRS}
)
target_link_libraries(
  ${PROJECT_NAME} PRIVATE
  ${Ruby_LIBRARIES}
)


if(MSVC AND CMAKE_JS_NODELIB_DEF AND CMAKE_JS_NODELIB_TARGET)
  # Generate node.lib
  execute_process(
    COMMAND ${CMAKE_AR}
    /def:${CMAKE_JS_NODELIB_DEF}
    /out:${CMAKE_JS_NODELIB_TARGET}
    ${CMAKE_STATIC_LINKER_FLAGS}
  )
endif()