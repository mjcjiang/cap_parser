LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/lib)

add_executable (test_cap_parser test_cap_parser.cc)
target_link_libraries(test_cap_parser src_lib)

