#!/bin/bash

if [[ $# -lt 1 ]]; then
	echo 'usage: bash cal_all_auth.sh category_of_damping_file'
else
	for param in $@; do
		echo "${param} file in processing..."
		### Category of damping coefficent prefix.
		CATE=${param}

		### Project Directory.
		DIR=~/code/project/dblp_circuit/
		### Damping coeff file name.
		DAMPING=${CATE}.damping
		### Edges information file name.
		EDGE_INFO=edges.info.2
		### Calculated authority file with respect to ${CATE}.
		OUT_FILE=${CATE}.auth

		${DIR}/build/main --all-node-influence ${DIR}/build/data/${EDGE_INFO} ${DIR}/build/resource/${DAMPING} | perl ${DIR}/script/disp_authority.pl ${DIR}/build/data/author.map > ${DIR}/build/data/${OUT_FILE}

	done 
fi
