cmake_minimum_required(VERSION 3.28)
project(pingtcp)

# Make project-provided Find modules available
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_executable(pingtcp "${CMAKE_CURRENT_SOURCE_DIR}/pingtcp.c")