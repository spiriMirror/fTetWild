find_package(spdlog CONFIG REQUIRED)
find_package(geogram CONFIG REQUIRED)
find_package(TBB CONFIG REQUIRED)
find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(gmp REQUIRED IMPORTED_TARGET gmp)

# ---------------------------------------------------------------------------------
# FloatTetwild Library
# ---------------------------------------------------------------------------------

add_library(FloatTetwild STATIC)

target_include_directories(FloatTetwild PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(FloatTetwild PUBLIC 
    # local
    libigl
    predicates         

    # vcpkg
    Geogram::geogram
    spdlog::spdlog
    Threads::Threads
    PkgConfig::gmp
    TBB::tbb
)

target_compile_definitions(FloatTetwild PUBLIC FLOAT_TETWILD_USE_TBB)

add_subdirectory(external)

set(SOURCES
    AABBWrapper.cpp
    auto_table.cpp
    CSGTreeParser.cpp
    LocalOperations.cpp
    EdgeSplitting.cpp
    EdgeCollapsing.cpp
    EdgeSwapping.cpp
    VertexSmoothing.cpp
    MeshImprovement.cpp
    FloatTetwild.cpp
    FloatTetDelaunay.cpp
    TriangleInsertion.cpp
    CutMesh.cpp
    intersections.cpp
    Simplification.cpp
    Mesh.cpp
    MeshIO.cpp
    Logger.cpp
)

target_sources(FloatTetwild PRIVATE ${SOURCES})

if(MSVC)
    # /source-charset:utf-8
    target_compile_options(FloatTetwild PUBLIC /source-charset:utf-8)
endif()
