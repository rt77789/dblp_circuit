
set(project_name "DBLP_CIRCUIT")

#IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
IF(${APPLE})
	# Mac OS X specific code
	SET(OS "MAC")
	#MESSAGE("${OperatingSystem}")
	#MESSAGE(${CMAKE_HOST_SYSTEM})
ELSEIF(${WIN32})
	SET(OS "WIN32")
ELSEIF(${UNIX})
	SET(OS "UNIX")
ENDIF(${APPLE})
#ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")



project(${project_name})

cmake_minimum_required(VERSION 2.6)

add_subdirectory(src)
ADD_SUBDIRECTORY(test)

aux_source_directory(src dir_srcs)

message("current project source dir: ${${project_name}_SOURCE_DIR}")
message("current project source dir: ${${project_name}_BINARY_DIR}")
MESSAGE(${CMAKE_SYSTEM_NAME})
MESSAGE(${CMAKE_SYSTEM_PROCESSOR})


INCLUDE_DIRECTORIES(${${project_name}_SOURCE_DIR}/src/)
INCLUDE_DIRECTORIES(${${project_name}_SOURCE_DIR}/include/)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/)

add_executable(main ${${project_name}_SOURCE_DIR}/main.cpp ${dir_srcs})

