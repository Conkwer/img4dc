cmake_minimum_required(VERSION 3.0)

project(img4dc)

ADD_DEFINITIONS("-Wall -Wpedantic -D_DEFAULT_SOURCE")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

add_subdirectory(common)
add_subdirectory(edc)
add_subdirectory(lbacalc)
add_subdirectory(cdi4dc)
add_subdirectory(mds4dc)


