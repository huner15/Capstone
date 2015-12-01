file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cc" "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(gp_lib STATIC ${SOURCE_FILES})
target_include_directories(gp_lib PUBLIC ${PROJECT_SOURCE_DIR}/inc)