cmake_minimum_required(VERSION 3.5)
include_directories ("${PROJECT_SOURCE_DIR}/Matrix")
add_subdirectory (Matrix)

# add the executable
add_executable (generate_ranking generate_ranking.cpp)
target_link_libraries (generate_ranking Matrix)
