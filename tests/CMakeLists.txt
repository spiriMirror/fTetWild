find_package(Catch2 CONFIG REQUIRED)

set(test_sources
    main.cpp
    tests.cpp
    test_predicates.cpp
    test_table.cpp

    # test_subdivision.cpp
    # test_tree.cpp
    # test_envelope.cpp
)

add_executable(unit_tests ${test_sources})

foreach(source IN ITEMS ${test_sources})
    source_group("tests" FILES "${source}")
endforeach()

target_link_libraries(unit_tests PRIVATE FloatTetwild Catch2::Catch2WithMain warnings::all)
