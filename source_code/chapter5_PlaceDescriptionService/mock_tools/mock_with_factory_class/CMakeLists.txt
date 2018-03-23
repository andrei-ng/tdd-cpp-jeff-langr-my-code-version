cmake_minimum_required(VERSION 2.8.2)

project(Chapter5_MockWithFactoryClass)

add_definitions(-std=c++0x)
#set(CMAKE_CXX_FLAGS "${CMAXE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

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
endif(JSONCPP_FOUND)

#set(CURL_LIBRARY "-lcurl")
pkg_check_modules(CURL libcurl REQUIRED)
#find_package(CURL)
if(CURL_FOUND)
  include_directories(${CURL_INCLUDE_DIRS})
  set(requiredlibs ${requiredlibs} ${CURL_LIBRARIES} )
else(CURL_FOUND)
  message(FATAL_ERROR "Could not find the CURL library and development files.")
endif(CURL_FOUND)

set(sources 
  main.cpp
  AddressExtractor.cpp
  PlaceDescriptionService.cpp
  AddressExtractor.h
  Address.h
  Http.h
  PlaceDescriptionService.h
  CurlHttp.cpp
  CurlHttp.h
  HttpFactory.cpp
)

set(sources_tests
	AddressExtractorTest.cpp
	PlaceDescriptionServiceTest.cpp
  CurlHttpTest.cpp
)

add_executable(test_with_factory ${sources} ${sources_tests})

target_link_libraries(test_with_factory gtest gmock_main pthread ${CURL_LIBRARIES} ${JSONCPP_LIBRARIES})
