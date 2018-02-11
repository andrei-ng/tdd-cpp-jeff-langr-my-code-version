cmake_minimum_required(VERSION 2.8.2)

project(chapter2SoundexExample)

add_definitions(-std=c++0x)
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall")

# Add CMake Modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
include(gtest)

set(sources 
    main.cpp
    string_utilities.cpp
    char_utilities.cpp
    Soundex.cpp
    SoundexTest.cpp)

add_executable(test_soundex ${sources})

target_link_libraries(test_soundex gtest gmock_main pthread)
