find_package(CLI11 CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)


add_executable(FloatTetwild_bin)
target_sources(FloatTetwild_bin PRIVATE main.cpp)
target_compile_features(FloatTetwild_bin PRIVATE ${CXX14_FEATURES})
target_link_libraries(FloatTetwild_bin
    PRIVATE
    FloatTetwild
    CLI11::CLI11
    nlohmann_json::nlohmann_json
)