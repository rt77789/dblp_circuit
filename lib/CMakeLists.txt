
#SET(LIB_SRC ../src/hash.cpp)

AUX_SOURCE_DIRECTORY(../src/ dir_srcs)

ADD_LIBRARY(main STATIC ${dir_srcs})
