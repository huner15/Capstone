include_directories("${PROJECT_SOURCE_DIR}/src")
add_executable(run_cdti main.cpp)
target_link_libraries(run_cdti cdti_lib capstone-shared)