#!/bin/sh

# to run a single faiss search on an input encoding vector file
# path to directories
src_dir="/home/sdp/precision-medicine/cpp/src/"
include_dir="/home/sdp/precision-medicine/cpp/include/"
conda_dir="/home/sdp/miniconda3/envs/pm/"
bin_dir="/home/sdp/precision-medicine/cpp/bin/"
data_dir="/home/sdp/precision-medicine/data/"

# path to encoded and query file
test_samples=$data_dir"samples/test_samples.txt"
train_samples=$data_dir"samples/train_samples.txt"
encoded_file=$data_dir"segments/chr8/seg_5000/chr8.seg.5.encoding"
k=80 # number of nearest neighbors to report
delim="space"

export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$conda_dir"lib"
echo $LD_LIBRARY_PATH
echo "Compiling..."


bin=$bin_dir"faiss_hnsw"
g++ $src_dir"faiss_hnsw.cpp" \
	$src_dir"build_index.cpp" \
	$src_dir"read_encodings.cpp" \
	$src_dir"search_index.cpp" \
	$src_dir"utils.cpp" \
	-I $include_dir \
	-I $conda_dir"include/" \
	-L $conda_dir"lib" \
	-lfaiss \
	-o $bin

echo "Executing..."

$bin $train_samples $encoded_file $test_samples $encoded_file $k $delim
