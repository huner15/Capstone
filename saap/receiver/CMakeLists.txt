project(saap)

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(run_saap ${SOURCE_FILES} inc/SurveillanceReport.h)
find_package(Protobuf REQUIRED)
target_link_libraries(run_saap saap_lib network_lib gp_lib jsonio_lib
        jsoncpp_lib ${PROTOBUF_LIBRARY})
target_include_directories(run_saap PUBLIC ${PROJECT_SOURCE_DIR}/inc)