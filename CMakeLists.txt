# ###############################################################################
cmake_minimum_required(VERSION 3.27)
project(FloatTetwild)

# ###############################################################################

# Detects whether this is a top-level project
get_directory_property(HAS_PARENT PARENT_DIRECTORY)

if(HAS_PARENT)
    set(FLOAT_TETWILD_TOPLEVEL_PROJECT OFF)
else()
    set(FLOAT_TETWILD_TOPLEVEL_PROJECT ON)
endif()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include(Warnings)

# spdlog
find_package(spdlog CONFIG REQUIRED)

# Geogram
find_package(geogram CONFIG REQUIRED)

# TBB
find_package(TBB CONFIG REQUIRED)

# C++11 threads
find_package(Threads REQUIRED)

if(FLOAT_TETWILD_TOPLEVEL_PROJECT)
    find_package(CLI11 CONFIG REQUIRED)
endif()


# ###############################################################################
# FloatTetwild library
# ###############################################################################

find_package(PkgConfig REQUIRED)
pkg_check_modules(gmp REQUIRED IMPORTED_TARGET gmp)

add_library(FloatTetwild STATIC)

# PUBLIC include directory for FloatTetwild
target_include_directories(FloatTetwild PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_subdirectory(external/libigl)
add_subdirectory(external/predicates)

# Other sources
add_subdirectory(src)

target_link_libraries(FloatTetwild PUBLIC libigl predicates)

target_link_libraries(FloatTetwild PUBLIC
    Geogram::geogram
    spdlog::spdlog
    Threads::Threads
    PkgConfig::gmp
    TBB::tbb
)

if(MSVC)
    # /source-charset:utf-8
    target_compile_options(FloatTetwild PUBLIC /source-charset:utf-8)
endif()

target_compile_definitions(FloatTetwild PUBLIC FLOAT_TETWILD_USE_TBB)


# ###############################################################################
# FloatTetwild API
# ###############################################################################

add_library(ftetwild SHARED)

target_link_libraries(ftetwild PRIVATE FloatTetwild)

find_package(Eigen3 CONFIG REQUIRED)

target_link_libraries(ftetwild INTERFACE Eigen3::Eigen)

target_compile_definitions(ftetwild PRIVATE -DFLOAT_TETWILD_EXPORT_DLL)

target_sources(ftetwild PRIVATE api/ftetwild.cpp)

# Export Header
target_include_directories(ftetwild PUBLIC 
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# ###############################################################################
# FloatTetwild binary
# ###############################################################################

# Main executable
if(FLOAT_TETWILD_TOPLEVEL_PROJECT)
    # Json
    find_package(nlohmann_json CONFIG REQUIRED)

    add_executable(FloatTetwild_bin)

    target_sources(FloatTetwild_bin PRIVATE src/main.cpp)
    
    target_compile_features(FloatTetwild_bin PRIVATE ${CXX14_FEATURES})

    target_link_libraries(FloatTetwild_bin
        PRIVATE
        FloatTetwild
        CLI11::CLI11
        nlohmann_json::nlohmann_json
    )

    target_compile_definitions(FloatTetwild_bin PRIVATE FLOAT_TETWILD_USE_TBB)
endif()

# ###############################################################################
# Subdirectories
# ###############################################################################



# Compile extras only if this is a top-level project
if(FLOAT_TETWILD_TOPLEVEL_PROJECT)
    # Unit tests
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif()

# Install
include(GNUInstallDirs)

install(TARGETS ftetwild
    EXPORT "ftetwildTargets"
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(EXPORT "ftetwildTargets"
FILE "ftetwildTargets.cmake"
NAMESPACE ftetwild::
DESTINATION share/ftetwild
)

install(FILES "${PROJECT_SOURCE_DIR}/cmake/ftetwildConfig.cmake"
DESTINATION share/ftetwild
)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/ftetwild"
DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})