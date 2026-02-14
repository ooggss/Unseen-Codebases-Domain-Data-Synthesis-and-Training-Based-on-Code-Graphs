#!/bin/bash
# bash build.sh release split_graph [index_prefix_path]
set -e

# Check arguments
if [ $# -lt 2 ]; then
  echo "Usage: ./build.sh [debug/release] [split_graph] [index_prefix_path]"
  echo "Example: ./build.sh release split_graph /path/to/index_prefix"
  exit 1
fi

# Get arguments
BUILD_TYPE=$1
ACTION=$2
INDEX_PREFIX_PATH=${3:-"/Users/yichuan/Desktop/code/LEANN/leann/diskannbuild/test_doc_files"}

# Calculate output path (parent directory of original path)
OUTPUT_DIR=$(dirname "$INDEX_PREFIX_PATH")
echo "Input index prefix: $INDEX_PREFIX_PATH"
echo "Output directory: $OUTPUT_DIR"

DATA_DIR="."
EMB_DIR="${DATA_DIR}/data/"

# Graph partition parameters
GP_TIMES=10
GP_USE_FREQ=0
GP_LOCK_NUMS=10
GP_CUT=100
GP_SCALE_F=1
DATA_TYPE=float
GP_T=10

# Path configuration
PREFIX=""
M=""
R=""
BUILD_L=""
B=""

GRAPH_PATH="${EMB_DIR}/starling/${PREFIX}_M${M}_R${R}_L${BUILD_L}_B${B}/GRAPH/"
GRAPH_GP_PATH="${GRAPH_PATH}GP_TIMES_${GP_TIMES}_LOCK_${GP_LOCK_NUMS}_GP_USE_FREQ${GP_USE_FREQ}_CUT${GP_CUT}_SCALE${GP_SCALE_F}/"

print_usage_and_exit() {
  echo "Usage: ./build.sh [debug/release] [split_graph]"
  exit 1
}

check_dir_and_make_if_absent() {
  local dir=$1
  if [ -d $dir ]; then
    echo "Directory $dir is already exit. Remove or rename it and then re-run."
    exit 1
  else
    mkdir -p ${dir}
  fi
}

# Build configuration
case $BUILD_TYPE in
  debug)
    # Check if we're being called as a subdirectory
    if [ -f "../CMakeLists.txt" ]; then
      # We're in a subdirectory, build from parent
      cmake -DCMAKE_BUILD_TYPE=Debug .. -B ${DATA_DIR}/build/debug
    else
      cmake -DCMAKE_BUILD_TYPE=Debug . -B ${DATA_DIR}/build/debug
    fi
    EXE_PATH=${DATA_DIR}/build/debug
  ;;
  release)
    # Check if we're being called as a subdirectory
    if [ -f "../CMakeLists.txt" ]; then
      # We're in a subdirectory, build from parent
      cmake -DCMAKE_BUILD_TYPE=Release .. -B ${DATA_DIR}/build/release
    else
      cmake -DCMAKE_BUILD_TYPE=Release . -B ${DATA_DIR}/build/release
    fi
    EXE_PATH=${DATA_DIR}/build/release
  ;;
  *)
    print_usage_and_exit
  ;;
esac

# Check if rebuild is needed
NEED_BUILD=true
if [ -f "${EXE_PATH}/graph_partition/partitioner" ] && [ -f "${EXE_PATH}/graph_partition/index_relayout" ]; then
  # Check if executables are newer than source files
  if [ "${EXE_PATH}/graph_partition/partitioner" -nt "src/partitioner.cpp" ] && \
     [ "${EXE_PATH}/graph_partition/partitioner" -nt "include/partitioner.h" ] && \
     [ "${EXE_PATH}/graph_partition/index_relayout" -nt "index_relayout.cpp" ] && \
     [ "${EXE_PATH}/graph_partition/partitioner" -nt "CMakeLists.txt" ]; then
    echo "Executables are up to date, skipping build..."
    NEED_BUILD=false
  fi
fi

if [ "$NEED_BUILD" = true ]; then
  echo "Building executables..."
  pushd $EXE_PATH
  make -j
  popd
else
  echo "Using existing executables..."
fi

mkdir -p ${DATA_DIR}/data

date
case $ACTION in
  split_graph)
    mkdir -p ${GRAPH_PATH}
    if [ -d ${GRAPH_GP_PATH} ]; then
      echo "Directory ${GRAPH_GP_PATH} is already exit."
      if [ -f "${GRAPH_GP_PATH}_part_tmp.index" ]; then
        echo "copy ${GRAPH_GP_PATH}_part_tmp.index to ${OUTPUT_DIR}/_disk_graph.index."
        GP_FILE_PATH=${GRAPH_GP_PATH}_part.bin
        cp ${GRAPH_GP_PATH}_part_tmp.index ${OUTPUT_DIR}/_disk_graph.index
        cp ${GP_FILE_PATH} ${OUTPUT_DIR}/_partition.bin
        exit 0
      else
        echo "${GRAPH_GP_PATH}_part_tmp.index not found."
        exit 1
      fi
    else
      mkdir -p ${GRAPH_GP_PATH}
      OLD_INDEX_FILE=${INDEX_PREFIX_PATH}_disk_beam_search.index
      if [ ! -f "$OLD_INDEX_FILE" ]; then
        OLD_INDEX_FILE=${INDEX_PREFIX_PATH}_disk.index
      fi
      
      GP_DATA_TYPE=$DATA_TYPE
      GP_FILE_PATH=${GRAPH_GP_PATH}_part.bin
                   echo "Running graph partition... ${GP_FILE_PATH}.log"
             if [ ${GP_USE_FREQ} -eq 1 ]; then
               echo "use freq"
               time ${EXE_PATH}/graph_partition/partitioner --index_file ${OLD_INDEX_FILE} \
                 --data_type $GP_DATA_TYPE --gp_file $GP_FILE_PATH -T $GP_T --ldg_times $GP_TIMES --freq_file ${FREQ_PATH}_freq.bin --lock_nums ${GP_LOCK_NUMS} --cut ${GP_CUT} --scale ${GP_SCALE_F} --mode 1 > ${GP_FILE_PATH}.log
             else
               echo "not using freq"
               echo "${EXE_PATH}/graph_partition/partitioner --index_file ${OLD_INDEX_FILE} \
                 --data_type $GP_DATA_TYPE --gp_file $GP_FILE_PATH -T $GP_T --ldg_times $GP_TIMES --scale ${GP_SCALE_F} --mode 1"
               time ${EXE_PATH}/graph_partition/partitioner --index_file ${OLD_INDEX_FILE} \
                 --data_type $GP_DATA_TYPE --gp_file $GP_FILE_PATH -T $GP_T --ldg_times $GP_TIMES --scale ${GP_SCALE_F} --mode 1 > ${GP_FILE_PATH}.log
             fi

      echo "Running relayout... ${GRAPH_GP_PATH}relayout.log"
      time ${EXE_PATH}/graph_partition/index_relayout ${OLD_INDEX_FILE} ${GP_FILE_PATH} $GP_DATA_TYPE 1 > ${GRAPH_GP_PATH}relayout.log
      
      echo "Copying results to ${OUTPUT_DIR}/"
      cp ${GRAPH_GP_PATH}_part_tmp.index ${OUTPUT_DIR}/_disk_graph.index
      cp ${GP_FILE_PATH} ${OUTPUT_DIR}/_partition.bin
      
      # Clean up temporary files
      echo "Cleaning up temporary files..."
      rm -rf data/
      echo "Temporary files cleaned up."
    fi
  ;;
  *)
    print_usage_and_exit
  ;;
esac 