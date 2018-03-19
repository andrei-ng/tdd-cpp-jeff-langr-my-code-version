cmake_minimum_required(VERSION 2.8.2)

project(Chapter5_DifficultExample)

add_definitions(-std=c++0x)
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall")

# Add CMake Modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
include(gtest)

set(sources 
  main.cpp
  OutParameterTest.cpp
)


add_executable(difficult_example ${sources} ${sources_tests})

target_link_libraries(difficult_example gtest gmock_main pthread ${JSONCPP_LIBRARIES})
