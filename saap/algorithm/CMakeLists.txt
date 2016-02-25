project(saap)

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(saap_lib STATIC ${SOURCE_FILES})
target_link_libraries(saap_lib util_lib gp_lib categorize_lib)
target_include_directories(saap_lib PUBLIC ${PROJECT_SOURCE_DIR}/inc
        PUBLIC ${PROJECT_SOURCE_DIR}/../reportReceiver/inc)