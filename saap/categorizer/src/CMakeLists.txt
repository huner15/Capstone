file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(categorizer_lib STATIC ${SOURCE_FILES})
target_link_libraries(categorizer_lib util_lib network_lib gp_lib jsonio_lib jsoncpp_lib algorithm_lib)
target_include_directories(categorizer_lib PUBLIC ${PROJECT_SOURCE_DIR}/inc)