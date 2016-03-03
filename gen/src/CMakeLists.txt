file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
#add_executable(run_gen ${SOURCE_FILES})
add_library(gen_lib STATIC ${SOURCE_FILES})
#target_include_directories(run_gen PUBLIC ${PROJECT_SOURCE_DIR}/inc)
target_include_directories(gen_lib PUBLIC ${PROJECT_SOURCE_DIR}/inc)
target_link_libraries(gen_lib gp_lib network_lib jsonio_lib jsoncpp_lib
        util_lib)

