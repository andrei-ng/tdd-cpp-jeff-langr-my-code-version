cmake_minimum_required(VERSION 2.8.2)

project(Chapter7_WavPublisher)

add_definitions(-std=c++0x)
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -DRLOG_COMPONENT=debug -Wall")

# Add CMake Modules to path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
include(gtest)

find_package(Boost $ENV{BOOST_VERSION} COMPONENTS filesystem system)
set(Boost_USE_STATIC_LIBS ON)
include_directories("${Boost_INCLUDE_DIRS}")
if (Boost_FOUND)
  message("Boost paths:")
  message("\tINCLUDE DIRS: ${Boost_INCLUDE_DIRS}")
  message("\tLIBRARIES: ${Boost_LIBRARIES}")
endif()

# Setup rlog variables
find_library(rlog_LIBRARY NAMES rlog)
find_path(rlog_INCLUDE_DIR rlog/rlog.h)
set(rlog_INCLUDE_DIR ${rlog_INCLUDE_DIR})
if (rlog_LIBRARY)
  message("Rlog paths:")
  message("\tINCLUDE DIRS: ${rlog_INCLUDE_DIR}")
  message("\tLIBRARIES: ${rlog_LIBRARY}")
endif()

set(sources WavReader.cpp WavDescriptor.cpp)
set(testSources WavReaderTest.cpp)

add_executable(utest testmain.cpp ${testSources} ${sources})
add_executable(SnippetPublisher main.cpp ${sources})

target_link_libraries(utest
  ${Boost_LIBRARIES}
  ${rlog_LIBRARY}
  gtest gmock_main
  pthread
  rlog)

target_link_libraries(SnippetPublisher
  ${Boost_LIBRARIES}
  ${rlog_LIBRARY}
  pthread
  rlog)
