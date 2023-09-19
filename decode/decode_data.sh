#!/usr/bin/env bash

set -e pipefail

### TODO: 
### modify these paths

python_src="/path/to/python_scripts/"
out_dir="/path/to/out_dir/"

my_samples="/path/to/my_samples.pns"
all_samples="/path/to/all_sample.pns"
good_samples="/path/to/avail_samples.pns"
chi="/path/to/chi.chi"
out_vcf=$out_dir"out.vcf"

cm_py="/path/to/addCM2map.py"
full_map="/path/to/full_map.map"
cmap="/path/to/cmap.cmap.gz"
out_map=$out_dir"out.map"

###
###

# remove bad ids from samples file
echo "1. Removing bad IDs from "$my_samples
python $python_src"decode/remove_bad_IDs.py" \
 --my_samples $my_samples \
 --all_samples $all_samples \
 --out_sample $good_samples

# make VCF file
echo "2. Preparing a VCF file."
chitools view -p $good_samples $chi -f vcf > $out_vcf
bgzip $out_vcf
tabix -p vcf $out_vcf".gz"

# make MAP file
echo "3. Preparing a MAP file."
awk '{ print $1 $2 $7 $3}' $full_map > $out_map
#python $cm_py $full_map $cmap

# makde PED file
echo "4. Preparing a PED file."

