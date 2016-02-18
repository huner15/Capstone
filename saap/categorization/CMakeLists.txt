project(saap)

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(categorize_lib STATIC ${SOURCE_FILES})
target_link_libraries(categorize_lib gp_lib saap_lib)
target_include_directories(categorize_lib PUBLIC ${PROJECT_SOURCE_DIR}/inc)