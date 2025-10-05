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

# Prepend function
include(PrependCurrentPath)

# FloatTetwild utils
include(FloatTetwildUtils)

include(Warnings)

# Sort projects inside the solution
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Generate position independent code by default
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Setup dependencies
include(FloatTetwildDependencies)

# ###############################################################################
# FloatTetwild library
# ###############################################################################

find_package(PkgConfig REQUIRED)
pkg_check_modules(gmp REQUIRED IMPORTED_TARGET gmp)

add_library(${PROJECT_NAME} STATIC)

# PUBLIC include directory for FloatTetwild
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR}/include)

add_subdirectory(external/libigl)
add_subdirectory(external/predicates)

target_link_libraries(${PROJECT_NAME} PUBLIC libigl predicates)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Geogram::geogram
    spdlog::spdlog
    Threads::Threads
    PkgConfig::gmp
    TBB::tbb
)

if(MSVC)
    # /source-charset:utf-8
    target_compile_options(${PROJECT_NAME} PUBLIC /source-charset:utf-8)
endif()

target_compile_definitions(${PROJECT_NAME} PUBLIC FLOAT_TETWILD_USE_TBB)


# ###############################################################################
# FloatTetwild API
# ###############################################################################

add_library(ftetwild SHARED)

target_link_libraries(ftetwild PRIVATE ${PROJECT_NAME})

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
    add_executable(${PROJECT_NAME}_bin src/main.cpp)
    target_compile_features(${PROJECT_NAME}_bin PRIVATE ${CXX14_FEATURES})

    target_link_libraries(${PROJECT_NAME}_bin
        PRIVATE
        ${PROJECT_NAME}
        CLI11::CLI11
        nlohmann_json::nlohmann_json
    )

    target_compile_definitions(${PROJECT_NAME}_bin PRIVATE FLOAT_TETWILD_USE_TBB)
endif()

# ###############################################################################
# Subdirectories
# ###############################################################################

# Other sources
add_subdirectory(src)

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
INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT "ftetwildTargets"
FILE "ftetwildTargets.cmake"
NAMESPACE ftetwild::
DESTINATION share/${PROJECT_NAME}
)

install(FILES "${PROJECT_SOURCE_DIR}/cmake/ftetwildConfig.cmake"
DESTINATION share/ftetwild
)