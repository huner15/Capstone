file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(util_lib STATIC ${SOURCE_FILES})
target_include_directories(util_lib PUBLIC ${PROJECT_SOURCE_DIR}/inc)
target_link_libraries(util_lib gp_lib jsonio_lib)