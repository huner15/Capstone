project(saap)

#add_subdirectory(inc)
#add_subdirectory(src)
#add_subdirectory(test)

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h")

add_executable(saap_lib ${SOURCE_FILES} ${HEADER_FILES})
#target_link_libraries(saap_lib util_lib)