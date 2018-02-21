project(rlog_stubbing)
cmake_minimum_required(VERSION 2.8.2)

add_definitions(-std=c++11)

set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -DRLOG_COMPONENT=debug -Wall")
set(sources rlog.cpp RLogChannel.cpp RLogNode.cpp StdioNode.cpp)

add_library(rlog_stub ${sources})

target_link_libraries(rlog_stub pthread)
