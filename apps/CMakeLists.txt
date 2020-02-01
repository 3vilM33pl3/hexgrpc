

add_executable(hexgrpc_server hexservercli.cpp)
target_compile_features(hexgrpc_server PRIVATE cxx_std_17)

target_link_libraries(hexgrpc_server PRIVATE hex_library Boost::program_options fmt::fmt)

add_executable(hexgrpc_client hexclientcli.cpp)
target_compile_features(hexgrpc_client PRIVATE cxx_std_17)

target_link_libraries(hexgrpc_client PRIVATE hex_library Boost::program_options fmt::fmt cli)

