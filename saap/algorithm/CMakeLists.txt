project(saap)

#add_subdirectory(inc)
#add_subdirectory(src)
#add_subdirectory(test)

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(saap_lib STATIC ${SOURCE_FILES})
target_link_libraries(saap_lib util_lib)
target_include_directories(saap_lib PUBLIC ${PROJECT_SOURCE_DIR}/inc)