project(saap)

add_subdirectory(test)

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
#    "${CMAKE_CURRENT_SOURCE_DIR}/test/*")

add_executable(run_saap ${SOURCE_FILES})
find_package(Protobuf REQUIRED)
target_link_libraries(run_saap categorize_lib util_lib network_lib
        gp_lib jsonio_lib jsoncpp_lib ${PROTOBUF_LIBRARY})
target_include_directories(run_saap PUBLIC ${PROJECT_SOURCE_DIR}/inc
        PUBLIC ${PROJECT_SOURCE_DIR}/../algorithm/inc)