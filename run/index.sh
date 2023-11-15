#!/usr/bin/env bash

set -e pipefail

pmed_dir=$1
out_dir=$2
config=$3

echo $pmed_dir
echo $out_dir
echo $config

## These directories should be correct.
## If you have changed where scripts exist, change these paths
smk_dir=$pmed_dir"workflow/"
log=$out_dir"log/index.log"
##
##

# for singularity container
#. /opt/conda/etc/profile.d/conda.sh
# load conda and activate snakemake env for run
#module load anaconda
#.~/miniconda3/bin/conda
#conda_dir="/home/sdp/miniconda3/envs/"
#source ~/miniconda3/etc/profile.d/mamba.sh 
#export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:~/miniconda3/condabin/conda
#conda activate snakemake

# activate conda / mamba
source  ~/.bashrc
# go to project directory
cd $pmed_dir

# run indexing pipeline
# 1. slice vcf
echo "1. slicing VCF..." > $log
start_slice=$(date +%s.%3N)
snakemake \
    -s $smk_dir"SLICE.smk" \
    -c 16 \
    -j 5 \
    --configfile=$config \
end_slice=$(date +%s.%3N)
slice_time=$(echo "scale=3; $end_slice - $start_slice" | bc)
echo "--SLICE: $slice_time seconds" >> $log

# 2. encode slices
echo "2. encode VCF slices..." >> $log
start_encode=$(date +%s.%3N)
snakemake \
    -s $smk_dir"ENCODE.smk" \
    -c 16 \
    -j 10 \
    --configfile=$config \
end_encode=$(date +%s.%3N)
encode_time=$(echo "scale=3; $end_encode - $start_encode" | bc)
echo "--ENCODE: $encode_time seconds" >> $log

# 3. embed slices
echo "3. embed slice encodings..." >> $log
start_embed=$(date +%s.%3N)
echo $start_embed
snakemake \
    -s $smk_dir"EMBED.smk" \
    -c 16 \
    -j 10 \
    --configfile=$config \
    --cluster-config $pmed_dir"run/embed_config.yml" \
    --cluster "sbatch -J {cluster.job-name} \\
                      -t {cluster.time} \\
                      -N {cluster.nodes} \\
                      -p {cluster.partition} \\
                      --ntasks-per-node {cluster.ntasks-per-node} \\
                      --nodelist={cluster.nodelist} \\
                      --gres={cluster.gpu} \\
                      --mem={cluster.mem} \\
                      --output {cluster.output} \\
                      --error {cluster.error}" \
    --latency-wait 70
end_embed=$(date +%s.%3N)
echo $end_embed
embed_time=$(echo "scale=3; $end_embed - $start_embed" | bc)
echo "--EMBED: $embed_time seconds" >> $log

# 4. index slices
echo "4. index slice embeddings..." >> $log
start_index=$(date +%s.%3N)
snakemake \
    -s $smk_dir"INDEX.smk" \
    -c 16 \
    -j 10 \
    --configfile=$config \
end_index=$(date +%s.%3N)
index_time=$(echo "scale=3; $end_index - $start_index" | bc)
echo "--INDEX: $index_time seconds" >> $log
