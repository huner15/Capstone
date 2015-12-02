add_executable(run_sim Server.cpp)
include(FindProtobuf)
find_package(Protobuf REQUIRED)
target_link_libraries(run_sim network_lib gp_lib ${PROTOBUF_LIBRARY})