file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(receiver_lib STATIC ${SOURCE_FILES})
target_link_libraries(receiver_lib util_lib gp_lib categorizer_lib algorithm_lib)
target_include_directories(receiver_lib PUBLIC ${PROJECT_SOURCE_DIR}/inc)