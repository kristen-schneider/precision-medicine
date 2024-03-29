#!/usr/bin/env bash

set -e pipefail

### TODO: 
### modify these paths

pmed_dir="/home/kristens/kristen-pmed/precision-medicine/"
smk_dir=$pmed_dir"smk_scripts/"
out_dir="/home/kristens/kristen-pmed/decode/"
log=$out_dir"pipeline.log"
config="/home/kristens/kristen-pmed/decode/decode_config.yml"

###
###

# go to project directory
cd $pmed_dir

# load conda and activate snakemake env for run
. /opt/conda/etc/profile.d/conda.sh
conda activate snakemake

# run pipeline
# 1. slice vcf
echo "1. slicing VCF..." > $log
start_slice=$(date +%s.%3N)
snakemake \
    -s $smk_dir"SLICE.smk" \
    -c 16 \
    -j 5 \
    --configfile=$config \
    --rerun-incomplete
end_slice=$(date +%s.%3N)
#slice_time=$(echo "scale=3; $end_slice - $start_slice" | bc)
#echo "--SLICE: $slice_time seconds" >> $log

# 2. encode slices
echo "2. encode VCF slices..." >> $log
start_encode=$(date +%s.%3N)
snakemake \
    -s $smk_dir"ENCODE.smk" \
    -c 16 \
    -j 10 \
    --use-conda \
    --conda-frontend mamba \
    --configfile=$config \
    --rerun-incomplete
end_encode=$(date +%s.%3N)
#encode_time=$(echo "scale=3; $end_encode - $start_encode" | bc)
#echo "--ENCODE: $encode_time seconds" >> $log

# 3. embed slices
echo "3. embed slice encodings..." >> $log
start_embed=$(date +%s.%3N)
echo $start_embed
snakemake \
    -s $smk_dir"EMBED.smk" \
    -c 16 \
    -j 10 \
    --use-conda \
    --conda-frontend mamba \
    --configfile=$config \
    --rerun-incomplete \
    #--cluster-config embed_config.yaml \
    #--cluster "sbatch -J {cluster.job-name} \\
    #                  -t {cluster.time} \\
    #                  -N {cluster.nodes} \\
    #                  -n {cluster.ntasks} \\
    #                  -p {cluster.partition} \\
    #                  --nodelist={cluster.nodelist} \\
    #                  --gres={cluster.gpu} \\
    #                  --mem={cluster.mem} \\
    #                  --output {cluster.output} \\
    #                  --error {cluster.error}" \
    #--latency-wait 70 \
end_embed=$(date +%s.%3N)
echo $end_embed
#embed_time=$(echo "scale=3; $end_embed - $start_embed" | bc)
#echo "--EMBED: $embed_time seconds" >> $log

# 4. index slices
echo "4. index slice embeddings..." >> $log
start_index=$(date +%s.%3N)
snakemake \
    -s $smk_dir"INDEX.smk" \
    -c 16 \
    -j 10 \
    --configfile=$config \
    --rerun-incomplete
    #--use-conda \
    #--conda-frontend mamba \
end_index=$(date +%s.%3N)
#index_time=$(echo "scale=3; $end_index - $start_index" | bc)
#echo "--INDEX: $index_time seconds" >> $log

# 5. search slices
echo "5. searching index slices..." >> $log
start_search=$(date +%s.%3N)
snakemake \
    -s $smk_dir"SEARCH.smk" \
    -c 16 \
    -j 10 \
    --use-conda \
    --conda-frontend mamba \
    --configfile=$config \
    --rerun-incomplete
end_search=$(date +%s.%3N)
#search_time=$(echo "scale=3; $end_search - $start_search" | bc)
#echo "--SEARCH: $search_time seconds" >> $log


# 6. aggregate slices
echo "6. aggregating results slices..." >> $log
start_aggregate=$(date +%s.%3N)
snakemake \
    -s $smk_dir"AGGREGATE.smk" \
    -c 16 \
    -j 10 \
    --use-conda \
    --conda-frontend mamba \
    --configfile=$config \
    --rerun-incomplete
end_aggregate=$(date +%s.%3N)
#aggregate_time=$(echo "scale=3; $end_aggregate - $start_aggregate" | bc)
#echo "--AGGREGATE: $aggregate_time seconds" >> $log


# 7. plot pedigree summary
echo "7. plotting results..." >> $log
start_plot=$(date +%s.%3N)
snakemake \
    -s $smk_dir"PLOT.smk" \
    -c 16 \
    -j 10 \
    --use-conda \
    --conda-frontend mamba \
    --configfile=$config \
    --rerun-incomplete
end_plot=$(date +%s.%3N)
#plot_time=$(echo "scale=3; $end_plot - $start_plot" | bc)
#echo "--PLOT: $plot_time seconds" >> $log
