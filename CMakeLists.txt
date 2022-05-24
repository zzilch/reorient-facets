cmake_minimum_required(VERSION 3.16)
project(reorient-facets)

list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Libigl
option(LIBIGL_EMBREE "Build target igl::embree" ON)
include(libigl)

# OpenMP
find_package(OpenMP)

# Build options
option(REOREINT_FACETS_EXE           "Build executable binary"        ON)
option(REOREINT_FACETS_PYTHON   "Build python module"           OFF)

if(REOREINT_FACETS_EXE)
    add_executable(reorient-facets src/exe.cpp)
    target_link_libraries(reorient-facets PUBLIC igl::embree)
    target_link_libraries(reorient-facets PUBLIC OpenMP::OpenMP_CXX)
endif()

if(REOREINT_FACETS_PYTHON)
    include(FetchContent)
    FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11
    GIT_TAG        v2.9.2
    )
    FetchContent_GetProperties(pybind11)
    if(NOT pybind11_POPULATED)
        FetchContent_Populate(pybind11)
        add_subdirectory(${pybind11_SOURCE_DIR} ${pybind11_BINARY_DIR})
    endif()
    pybind11_add_module(reorient_facets MODULE src/module.cpp)
    target_link_libraries(reorient_facets PUBLIC igl::embree)
    target_link_libraries(reorient_facets PUBLIC OpenMP::OpenMP_CXX)
endif()