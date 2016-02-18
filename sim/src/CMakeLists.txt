file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(run_sim ${SOURCE_FILES})
target_include_directories(run_sim PUBLIC ${PROJECT_SOURCE_DIR}/inc)
target_link_libraries(run_sim gp_lib network_lib jsonio_lib jsoncpp_lib
        util_lib)