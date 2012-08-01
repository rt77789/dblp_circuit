
MESSAGE("Unit Test Here.")

AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/test/ dir_test)
AUX_SOURCE_DIRECTORY(${PROJECT_SOURCE_DIR}/src/ dir_srcs)


INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src/)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include/)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib/)

ADD_EXECUTABLE(test_all ${dir_srcs} ${dir_test})
#ADD_EXECUTABLE(test_main ${dir_srcs} main.cpp)

MESSAGE(${PROJECT_SOURCE_DIR}/lib)

#FIND_LIBRARY(extra_libs libgtest.a) 
#IF(extra_libs) 
#	INCLUDE_DIRECTORIES(${extra_libs}) 
#ELSE(extra_libs)
#	MESSAGE("Can't find gtest lib path.")
#ENDIF(extra_libs)
#
IF(${APPLE})
	SET(libgtest_main "libgtest_main_mac.a")
	SET(libgtest "libgtest_mac.a")
ELSEIF(${WIN32})

ELSEIF(${UNIX})
	SET(libgtest_main "libgtest_main.a")
	SET(libgtest "libgtest.a")
ENDIF(${APPLE})

TARGET_LINK_LIBRARIES(test_all
	pthread
	${libgtest_main}
	${libgtest})
