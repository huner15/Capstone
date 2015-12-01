add_executable(run_sim Server.cpp)
target_link_libraries(run_sim network_lib gp_lib protobuf)