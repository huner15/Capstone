file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(algorithm_lib STATIC ${SOURCE_FILES})
target_link_libraries(algorithm_lib util_lib gp_lib categorizer_lib receiver_lib)
target_include_directories(algorithm_lib PUBLIC ${PROJECT_SOURCE_DIR}/inc)