#!/bin/bash

## File name of input data, e.g. dblp.xml -> dblp, without suffix.
FILE_NAME=dblp
PROJECT_DIR=..
DATA_DIR=../build/data

###
perl extract.pl ${DATA_DIR}/${FILE_NAME}.xml > ${DATA_DIR}/${FILE_NAME}.raw
echo "extract.pl finish..."

###
perl author_hash.pl ${DATA_DIR}/${FILE_NAME}_author.map ${DATA_DIR}/${FILE_NAME}_conf.map < ${DATA_DIR}/${FILE_NAME}.raw > ${DATA_DIR}/${FILE_NAME}.hashed
echo "author_hash.pl finish..."

###
perl cal_weight.pl < ${DATA_DIR}/${FILE_NAME}.hashed > ${DATA_DIR}/${FILE_NAME}_edges.info
echo "cal_weight.pl finish..."

### 
perl ext_conf_name.pl < ${DATA_DIR}/cs_conf_rank.html > ${DATA_DIR}/conf.cate
echo "ext_conf_name.pl finish..."

###
perl cal_damping.pl ${DATA_DIR}/${FILE_NAME}.hashed ${DATA_DIR}/conf.cate ${DATA_DIR}/${FILE_NAME}_conf.map ${DATA_DIR}
echo "cal_damping.pl finish..."
