file(GLOB SOURCE_FILES "algorithm/Prediction.cpp" "algorithm/Cluster.cpp" "Categorization/Categorizor.cpp")
file(GLOB HEADER_FILES "../inc/algorithm/Prediction.h" "../inc/algorithm/Cluster.h" "../inc/Categorization/Categorizor.h")
file(GLOB SOURCE_FILES ${HEADER_FILES} ${SOURCE_FILES} )
add_subdirectory(reportReceiver)