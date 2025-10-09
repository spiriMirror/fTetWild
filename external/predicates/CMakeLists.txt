cmake_minimum_required(VERSION 3.27)
project(predicates)

add_library(${PROJECT_NAME} STATIC predicates.c predicates.h)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Generate position independent code
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
