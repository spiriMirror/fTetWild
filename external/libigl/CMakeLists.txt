find_package(Eigen3 CONFIG REQUIRED)
add_library(libigl INTERFACE)
target_include_directories(libigl INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(libigl INTERFACE Eigen3::Eigen)