file(GLOB SOURCE_FILES "algorithm/Prediction.cpp" "algorithm/Cluster.cpp")
file(GLOB HEADER_FILES "../inc/algorithm/Prediction.h" "../inc/algorithm/Cluster.h")
add_library(saap_lib ${HEADER_FILES} ${SOURCE_FILES})
add_subdirectory(reportReceiver)