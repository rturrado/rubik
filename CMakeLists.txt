cmake_minimum_required(VERSION 3.22)

project("rubik"
    VERSION 1.0
    DESCRIPTION "An OpenGL implementation of a Rubik's cube."
    HOMEPAGE_URL https://github.com/rturrado/rubik.git
    LANGUAGES C CXX
    )

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(src)
