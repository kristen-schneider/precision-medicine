#!/usr/bin/env bash

#SBATCH --partition=short
#SBATCH --job-name=plink-benchmark
#SBATCH --output=/Users/krsc0813/1KG_data/chr1_22/out/plink-benchmark.out
#SBATCH --error=/Users/krsc0813/1KG_data/chr1_22/err/plink-benchmark.err
#SBATCH --time=0-23:00:00
#SBATCH --qos=normal
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --mail-type=NONE
#SBATCH --mail-user=krsc0813@colorado.edu

# This script shows an example of how we ran
# plink --genome and 
# plink2 --make-king-table

# TODO: fill in file paths appropriately.
vcf="/Users/krsc0813/1KG_data/chr1_22/chrm_1-22.vcf.gz"
data_dir="/Users/krsc0813/1KG_data/chr1_22"

cd $data_dir
echo "plink --genome"
plink --vcf $vcf \
       	--genome \
	--out $data_dir"/plink-genome"

echo "plink2 --kinship"
plink2 --vcf $vcf --make-king-table
