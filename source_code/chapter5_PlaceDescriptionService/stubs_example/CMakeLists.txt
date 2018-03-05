cmake_minimum_required(VERSION 2.8.2)

project(Chapter5_TddTestStubs)

add_definitions(-std=c++0x)
set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall")

# Add CMake Modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
include(gtest)

# Find the JsonCpp library
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp REQUIRED)
include_directories("${JSONCPP_INCLUDE_DIRS}")
if (JSONCPP_FOUND)
  message("INCLUDE DIRS: ${JSONCPP_INCLUDE_DIRS}")
  message("LIBRARIES: ${JSONCPP_LIBRARIES}")
endif()

set(sources 
  main.cpp
  AddressExtractor.cpp
#  CurlHttp.cpp
  PlaceDescriptionService.cpp
  AddressExtractor.h
  Address.h
#  CurlHttp.h
  Http.h
  PlaceDescriptionService.h
)

set(sources_tests
	AddressExtractorTest.cpp
#	CurlHttpTest.cpp
	PlaceDescriptionServiceTest.cpp
)

add_executable(test_pds_wstubs ${sources} ${sources_tests})

target_link_libraries(test_pds_wstubs gtest gmock_main pthread ${JSONCPP_LIBRARIES})
