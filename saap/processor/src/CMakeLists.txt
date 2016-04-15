file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(run_saap ${SOURCE_FILES})
target_include_directories(run_saap PUBLIC ${PROJECT_SOURCE_DIR}/inc)
find_package(Protobuf REQUIRED)
target_link_libraries(run_saap categorizer_lib util_lib network_lib gp_lib
        jsonio_lib jsoncpp_lib receiver_lib algorithm_lib ${PROTOBUF_LIBRARY})