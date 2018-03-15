cmake_minimum_required(VERSION 2.8.2)

project(Chapter4_ParameterizedTestExample)

add_definitions(-std=c++0x)
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall")

# Add CMake Modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
include(gtest)

set(sources 
  main.cpp
  ParameterizedTest.cpp)

set(UNIT_TEST parametrized_test)

add_executable(${UNIT_TEST} ${sources})

target_link_libraries(${UNIT_TEST} gtest gmock_main pthread)

## Run tests as part of the build step
#add_custom_command(
#     TARGET ${UNIT_TEST}
#     COMMENT "Runing tests"
#     POST_BUILD
#     COMMAND ${UNIT_TEST}
#)
