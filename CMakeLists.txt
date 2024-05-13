cmake_minimum_required(VERSION 3.11)

#  Curve-X library
project(curve_x)
set(CMAKE_CXX_STANDARD 17)

#  List all .cpp files
file(GLOB_RECURSE CURVE_X_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

#  Declare library with sources and headers
add_library(curve_x)
target_include_directories(curve_x PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_sources(curve_x PRIVATE "${CURVE_X_SOURCES}")

#  Declare test executable
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
	add_executable(curve_x_main "tests/main.cpp")
	target_link_libraries(curve_x_main PRIVATE curve_x)

	add_executable(curve_x_simple_example "tests/simple_example.cpp")
	target_link_libraries(curve_x_simple_example PRIVATE curve_x)

	message("Included Curve-X test")
else()
	message("Skipped Curve-X test")
endif ()