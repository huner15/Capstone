include_directories("${PROJECT_SOURCE_DIR}/src")
add_executable(run_sim main.cpp)
target_link_libraries(run_sim sim_lib gp_lib)