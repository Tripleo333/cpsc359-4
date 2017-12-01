set (PROJ_NAME 359_A4)
cmake_minimum_required(VERSION 3.5)
project("${PROJ_NAME}")

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wconversion")

include_directories("${CMAKE_SOURCE_DIR}/include")

file(GLOB SOURCES include/*.h src/*.c)

add_executable("${PROJ_NAME}" ${SOURCES})
