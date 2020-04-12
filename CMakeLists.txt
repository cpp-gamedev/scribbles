cmake_minimum_required(VERSION 3.13)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
	message(FATAL_ERROR "In-Source Builds Not Allowed")
endif()

set(CMAKE_BUILD_TYPE Debug)
set(NAME scribbles)

project(${NAME})

add_executable(${NAME}
	main.cpp
)

set(COMPILE_OPTIONS -Wextra -Werror=return-type)
target_compile_options(${NAME} PUBLIC ${COMPILE_OPTIONS})
