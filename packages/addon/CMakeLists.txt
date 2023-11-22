cmake_minimum_required(VERSION 3.5.0)
cmake_policy(SET CMP0091 NEW)
cmake_policy(SET CMP0042 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")


project (addon)

add_definitions(-DNAPI_VERSION=4)

include_directories(${CMAKE_JS_INC})
include_directories("/usr/include/")
include_directories("/run/media/home/common/gabrielmartins.dev/dev/cpp/orm-xp/orm-node/packages/core/include")


file(GLOB SOURCE_FILES "src/addon.cpp")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})

target_link_libraries(${PROJECT_NAME} PRIVATE 
    /run/media/home/common/gabrielmartins.dev/dev/cpp/orm-xp/orm-node/packages/core/lib/libORM-Core.a
)

# Boost Filesystem
find_package(Boost REQUIRED COMPONENTS system filesystem)
target_link_libraries(${PROJECT_NAME} PRIVATE
    Boost::boost
    Boost::atomic
    Boost::system
    Boost::filesystem
)

find_package(Ruby REQUIRED)
include_directories(${Ruby_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${RUBY_LIBRARY})

if(MSVC AND CMAKE_JS_NODELIB_DEF AND CMAKE_JS_NODELIB_TARGET)
  # Generate node.lib
  execute_process(COMMAND ${CMAKE_AR} /def:${CMAKE_JS_NODELIB_DEF} /out:${CMAKE_JS_NODELIB_TARGET} ${CMAKE_STATIC_LINKER_FLAGS})
endif()