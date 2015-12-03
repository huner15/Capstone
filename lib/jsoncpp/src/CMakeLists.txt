file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_library(jsoncpp_lib STATIC ${SOURCE_FILES})
target_include_directories(jsoncpp_lib PUBLIC ${PROJECT_SOURCE_DIR}/inc)