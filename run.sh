#!/usr/bin/env bash

#SBATCH -p short
#SBATCH --job-name=chr10
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=16
#SBATCH --mem=64gb
#SBATCH --time=23:00:00
#SBATCH --mail-type=NONE
#SBATCH --mail-user=krsc0813@colorado.edu
#SBATCH --output=/Users/krsc0813/precision-medicine/slurm_scripts/out/chr10.out
#SBATCH --error=/Users/krsc0813/precision-medicine/slurm_scripts/err/chr10.err

set -e pipefail

pmed_dir="/Users/krsc0813/precision-medicine/"
data_dir="/Users/krsc0813/chr10/"
#data_dir=$pmed_dir"example/"

log=$data_dir"pipeline.log"

# go to project directory and update
cd $pmed_dir
git submodule init
git submodule update

# run pipeline

# 1. slice vcf
echo "1. slicing VCF..." > $log
start_slice=$(date +%s.%3N)
snakemake \
    -s SLICE.smk \
    -c 16 \
    -j 5 \
    --use-conda \
    --conda-frontend mamba \
    --rerun-incomplete
end_slice=$(date +%s.%3N)
slice_time=$(echo "scale=3; $end_slice - $start_slice" | bc)
echo "--SLICE: $slice_time miliseconds" >> $log

# 2. encode slices
echo "2. encode VCF slices..." >> $log
start_encode=$(date +%s.%3N)
snakemake \
    -s ENCODE.smk \
    -c 16 \
    -j 10 \
    --use-conda \
    --conda-frontend mamba \
    --rerun-incomplete
end_encode=$(date +%s.%3N)
encode_time=$(echo "scale=3; $end_encode - $start_encode" | bc)
echo "--ENCODE: $encode_time miliseconds" >> $log

# 3. embed slices
echo "3. embed slice encodings..." >> $log
start_embed=$(date +%s.%3N)
echo $start_embed
snakemake \
    -s EMBED.smk \
    -c 16 \
    -j 10 \
    --use-conda \
    --conda-frontend mamba \
    --cluster-config embed_config.yaml \
    --cluster "sbatch -J {cluster.job-name} \\
                      -t {cluster.time} \\
                      -N {cluster.nodes} \\
                      -n {cluster.ntasks} \\
                      -p {cluster.partition} \\
                      --mem={cluster.mem} \\
                      --output {cluster.output} \\
                      --error {cluster.error}" \
    --rerun-incomplete
end_embed=$(date +%s.%3N)
echo $end_embed
embed_time=$(echo "scale=3; $end_embed - $start_embed" | bc)
echo "--EMBED: $embed_time miliseconds" >> $log

# 4. index slices
echo "4. index slice embeddings..." >> $log
start_index=$(date +%s.%3N)
snakemake \
    -s INDEX.smk \
    -c 16 \
    -j 10 \
    --use-conda \
    --conda-frontend mamba \
    --rerun-incomplete
end_index=$(date +%s.%3N)
index_time=$(echo "scale=3; $end_index - $start_index" | bc)
echo "--INDEX: $index_time miliseconds" >> $log

# 5. search slices
echo "5. searching index slices..." >> $log
start_search=$(date +%s.%3N)
snakemake \
    -s SEARCH.smk \
    -c 16 \
    -j 10 \
    --use-conda \
    --conda-frontend mamba \
    --rerun-incomplete
end_search=$(date +%s.%3N)
search_time=$(echo "scale=3; $end_search - $start_search" | bc)
echo "--SEARCH: $search_time miliseconds" >> $log