include_directories("${PROJECT_SOURCE_DIR}/src")

add_executable(run_saap main.cpp)

target_link_libraries(run_saap saap_lib)