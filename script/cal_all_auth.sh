#!/bin/bash

if [[ $# -lt 1 ]]; then
	echo 'usage: bash cal_all_auth.sh category_of_damping_file'
else
	#		### Project Directory.
	PROJECT_DIR=~/code/project/dblp_circuit/
	DIR=~/code/project/dblp_circuit/build
	DATA_DIR=${DIR}/data
	FILE_NAME=dblp

	PLIST=$@
	#INFLUCENT_OPTION=--all-node-influence
	INFLUCENT_OPTION=--single-influence

	if [[ $1 == '--all' ]]; then
		PLIST=`ls ${DATA_DIR}/*.damping`
	fi
	for param in ${PLIST[*]}; do
		param=${param##*/}
		param=${param%%.*}
#		echo ${param}

		echo "${param} file in processing..."
		### Category of damping coefficent prefix.
		CATE=${param}

		### Damping coeff file name.
		DAMPING=${CATE}.damping
		### Edges information file name.
		EDGE_INFO=${FILE_NAME}_edges.info
		### Calculated authority file with respect to ${CATE}.
		OUT_FILE=${CATE}.auth

		${DIR}/main ${INFLUCENT_OPTION} ${DATA_DIR}/${EDGE_INFO} ${DATA_DIR}/${DAMPING} | perl ${PROJECT_DIR}/script/disp_authority.pl ${DATA_DIR}/${FILE_NAME}_author.map > ${DATA_DIR}/${OUT_FILE}

	done	
fi
