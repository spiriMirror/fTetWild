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
