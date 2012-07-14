
set(project_name "DBLP_CIRCUIT")

project(${project_name})

cmake_minimum_required(VERSION 2.6)

add_subdirectory(src)
ADD_SUBDIRECTORY(test)

aux_source_directory(src dir_srcs)

message("current project source dir: ${${project_name}_SOURCE_DIR}")
message("current project source dir: ${${project_name}_BINARY_DIR}")

INCLUDE_DIRECTORIES(./src/)
INCLUDE_DIRECTORIES(./include/)

add_executable(main ${${project_name}_SOURCE_DIR}/main.cpp ${dir_srcs})

