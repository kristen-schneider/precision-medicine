## Building Model/Training on Data
To experiment with the model, run the python script `main.py` in  `python/scripts/cnn/`.<br>
*NOTE: this script does not use the `model.py` script.*<br>
<br>
This script takes 4 arguments:<br>
1. input: path to file with all sample IDs
2. input: path to file with all sample encodings (for one segment)
3. input: path to file with cnn input format
- format: `sample1_ID, sample2_ID, plink_distance`<br>
- this can be generated by`python/scripts/cnn/make_CNN_input.py`
4. output: path to file where output embeddings will be written (e.g. `data/toy_model_data/chr6.seg.0.embeddings`)

```
python /
  python/scripts/cnn/main.py \
  data/toy_model_data/ALL.sampleIDs \
  data/toy_model_data/chr6.seg.0.encodings \
  data/toy_model_data/chr6.seg.0.cnn \
  data/toy_model_data/chr6.seg.0.embeddings
```
<br>

## Running full pipline (vcf-->distances)
### 1. Activating mamba environment
*creating environment from environment.yml (recommended)*<br>
`mamba env create -f environment.yml`<br>
*creating new environment with mamba*<br>
`mamba create -c conda-forge -c bioconda -n precision-medicine snakemake htslib plink faiss tensorflow`<br>
<br>

### 2. Editing config files
- edit `cpp/configs/segment_config`<br>
- edit `config.yaml`<br>
<br>

### 3. Running with snakemake
run `snakemake`

