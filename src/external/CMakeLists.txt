set(SOURCES
    Predicates.cpp
    mesh_AABB.cpp
    MshSaver.cpp
    MshLoader.cpp
    triangle_triangle_intersection.cpp
    getRSS.c
    get_mem.cpp
    bfs_orient.cpp
)

target_sources(FloatTetwild PRIVATE ${SOURCES})
