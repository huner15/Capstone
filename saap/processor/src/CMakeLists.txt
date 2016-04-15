file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(run_saap ${SOURCE_FILES})
target_include_directories(run_saap PUBLIC ${PROJECT_SOURCE_DIR}/inc)
target_link_libraries(run_saap gp_lib network_lib jsonio_lib jsoncpp_lib
        util_lib categorize_lib algorithm_lib receiver_lib)