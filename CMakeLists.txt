cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
	message(FATAL_ERROR "In-Source Builds Not Allowed")
endif()

set(BUILD_CONFIG Debug)
set(CMAKE_BUILD_TYPE ${BUILD_CONFIG})
set(NAME scribbles)

project(${NAME})

add_subdirectory(lib)

add_executable(${NAME} main.cpp)

target_link_libraries(${NAME} PUBLIC "${NAME}Library" stdc++fs)

set(COMPILE_OPTIONS -Wextra -Werror=return-type)
target_compile_options(${NAME} PUBLIC ${COMPILE_OPTIONS})