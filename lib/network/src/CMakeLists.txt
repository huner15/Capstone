file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(network_lib STATIC ${SOURCE_FILES})
target_include_directories(network_lib PUBLIC ${PROJECT_SOURCE_DIR}/inc)