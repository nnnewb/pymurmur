cmake_minimum_required(VERSION 3.26)
project(pymurmur LANGUAGES C CXX)

find_package(Python3 REQUIRED COMPONENTS Development.SABIModule)

file(
    GLOB_RECURSE
    PYMURMUR_SOURCES
    src/*.c
    src/*.cpp
    src/*.h
    src/**/*.c
    src/**/*.cpp
    src/**/*.h
)

Python3_add_library(${PROJECT_NAME} MODULE USE_SABI 3.3 ${PYMURMUR_SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES C_STANDARD 99)
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8 /MT /Zi /EHsc /Wall)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif ()