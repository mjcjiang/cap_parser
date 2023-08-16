CMAKE_MINIMUM_REQUIRED(VERSION 3.12)
PROJECT(cap_parser)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-copy-dt-needed-entries")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

############################################################
include_directories(deps/json-3.11.2/single_include)
include_directories(deps/spdlog-1.11.0/include)

include_directories(include)

file(COPY ${CMAKE_SOURCE_DIR}/files DESTINATION apps)
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")

add_subdirectory(deps)
add_subdirectory(src)
add_subdirectory(apps)
