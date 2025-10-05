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

# Json
find_package(nlohmann_json CONFIG REQUIRED)