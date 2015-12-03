file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(jsonio_lib STATIC ${SOURCE_FILES})
target_link_libraries(jsonio_lib jsoncpp_lib)
target_include_directories(jsonio_lib PUBLIC ${PROJECT_SOURCE_DIR}/inc)