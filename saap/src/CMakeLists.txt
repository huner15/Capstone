file(GLOB HEADER_FILES "algorithm/Prediction.h" "algorithm/Cluster.h")
file(GLOB SOURCE_FILES "algorithm/Prediction.cpp" "algorithm/Cluster.cpp")
add_library(saap_lib ${HEADER_FILES} ${SOURCE_FILES})