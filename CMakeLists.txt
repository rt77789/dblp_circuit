
set(project_name "DBLP_CIRCUIT")

project(${project_name})

cmake_minimum_required(VERSION 2.6)

add_subdirectory(src)
ADD_SUBDIRECTORY(test)

aux_source_directory(src dir_srcs)

message("current project source dir: ${${project_name}_SOURCE_DIR}")
message("current project source dir: ${${project_name}_BINARY_DIR}")

INCLUDE_DIRECTORIES(${${project_name}_SOURCE_DIR}/src/)
INCLUDE_DIRECTORIES(${${project_name}_SOURCE_DIR}/include/)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/)

add_executable(main ${${project_name}_SOURCE_DIR}/main.cpp ${dir_srcs})

