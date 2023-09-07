#!/usr/bin/env bash

#SBATCH -p short
#SBATCH --job-name=clean
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=16
#SBATCH --mem=64gb
#SBATCH --time=1:00:00
#SBATCH --mail-type=NONE
#SBATCH --mail-user=krsc0813@colorado.edu
#SBATCH --output=/Users/krsc0813/precision-medicine/run_singularity/out/clean.out
#SBATCH --error=/Users/krsc0813/precision-medicine/run_singularity/err/clean.err

#data_dir='/Users/krsc0813/chr10/'
#data_dir='/Users/krsc0813/chr10_12/'
#data_dir='/Users/krsc0813/AFR_pedigree/'
data_dir='/Users/krsc0813/precision-medicine/example/'

rm /Users/krsc0813/precision-medicine/run_singularity/err/example.err
rm /Users/krsc0813/precision-medicine/run_singularity/out/example.out

# go to data directory 
cd $data_dir

rm *.txt
rm pipeline.log
rm segment_boundary.map
rm interpolated.map

rm -r log/
rm -r benchmark/
rm -r vcf_segments/
rm -r encodings/
rm -r embeddings/
rm -r faiss_index/
rm -r faiss_results/
rm -r faiss_sample_results/
rm -r svs_index/
rm -r svs_results/
rm -r svs_sample_results/