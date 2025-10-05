cmake_minimum_required(VERSION 3.27)
project(FloatTetwild)

option(FLOAT_TETWILD_BUILD_TESTS "Build tests" ON)
option(FLOAT_TETWILD_BUILD_CLI "Build command line interface application" ON)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(Warnings)

# External Dependencies
add_subdirectory(external/libigl)
add_subdirectory(external/predicates)

# Main Library
add_subdirectory(src/floattetwild)

# API Library
add_subdirectory(src/ftetwild)

if(FLOAT_TETWILD_BUILD_CLI)
    add_subdirectory(app)
endif()


if(FLOAT_TETWILD_BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()
