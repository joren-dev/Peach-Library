cmake_minimum_required(VERSION 3.16.5)

project(PeachLibrary)

set(CMAKE_CXX_STANDARD 20)

add_library(PeachLibrary STATIC
        pe_exceptions/core/pe_normal_exception.cpp
        )

set_target_properties(PeachLibrary PROPERTIES LINKER_LANGUAGE CXX)
