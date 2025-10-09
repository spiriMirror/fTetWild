# ---------------------------------------------------------------------
# ftetwild Library
# ---------------------------------------------------------------------

add_library(ftetwild SHARED)

target_link_libraries(ftetwild PRIVATE FloatTetwild)

find_package(Eigen3 CONFIG REQUIRED)

target_link_libraries(ftetwild INTERFACE Eigen3::Eigen)

target_compile_definitions(ftetwild PRIVATE -DFLOAT_TETWILD_EXPORT_DLL)

file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

target_sources(ftetwild PRIVATE ${SOURCES})

# Export Header
target_include_directories(ftetwild PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

if (FLOAT_TETWILD_BUILD_TESTS)
    add_executable(ftetwild_test test/main.cpp)
    target_link_libraries(ftetwild_test PRIVATE ftetwild)
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
    DESTINATION share/ftetwild
)

install(FILES "${PROJECT_SOURCE_DIR}/cmake/ftetwildConfig.cmake"
    DESTINATION share/ftetwild
)

install(DIRECTORY "${PROJECT_SOURCE_DIR}/include/ftetwild"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)