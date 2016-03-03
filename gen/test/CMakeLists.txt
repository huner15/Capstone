include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${gtest_SOURCE_DIR}/inc ${gtest_SOURCE_DIR})
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
add_executable(run_gen_tests ${SOURCE_FILES} SimulationGeneratorTests.cpp)
target_link_libraries(run_gen_tests gen_lib gtest gtest_main util_lib)


