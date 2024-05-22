cmake_minimum_required(VERSION 3.11)

#  Curve-X library
project(curve-x)
set(CMAKE_CXX_STANDARD 17)

#  List all .cpp files
file(GLOB_RECURSE CURVE_X_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

#  Declare library with sources and headers
add_library(curve-x)
target_include_directories(curve-x PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_sources(curve-x PRIVATE "${CURVE_X_SOURCES}")

#  Declare test executable
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
	add_executable(curve-x-main "tests/main.cpp")
	target_link_libraries(curve-x-main PRIVATE curve-x)

	add_executable(curve-x-simple_example "tests/simple_example.cpp")
	target_link_libraries(curve-x-simple_example PRIVATE curve-x)

	message("Included Curve-X test")
else()
	message("Skipped Curve-X test")
endif ()