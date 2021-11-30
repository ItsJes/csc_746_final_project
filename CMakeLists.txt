cmake_minimum_required(VERSION 3.14)
project(hw2 LANGUAGES C CXX)

set(CMAKE_BUILD_TYPE "Release")

find_package(BLAS REQUIRED)

# We require the GNU compiler for this assignment.
if (NOT "${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    set(Prg-Intel "PrgEnv-intel")
    set(Prg-Clang "PrgEnv-cray")
    message(WARNING
            "Must use GNU Compiler for submission. Make sure you ran:\n"
            "module swap ${Prg-${CMAKE_C_COMPILER_ID}} PrgEnv-gnu")
endif ()

# Common library target for benchmarking.

add_executable(quicksort-basic quicksort-basic.cpp)
add_executable(quicksort-openmp quicksort-openmp.cpp)



