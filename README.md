### How to run the full pipeline (vcf-->summary distances)
#### 0. Clone the latest version of the repository.
#### 1. Create and activate the mamba environment.
`mamba env create -f environment.yml`<br>
`mamba activate pm`
#### 2. Create new yaml file for snakemake options. (See below for more information)
- create a new directory to house your data `mkdir ./my_dir`
- create a new directory to house your segments `mkdir ./my_dir/segments`
- create a new config file `<snakemake_config_file>.yaml`
- follow example at [`./my_dir/config_ex_snakemake.yaml`](https://github.com/kristen-schneider/precision-medicine/blob/main/data/example_data/config_ex_snakemake.yaml). Modify the following options to reflect appropriate file paths.
  ```
  home_dir:
    /path/to/project/directory/
  conda_dir:
    /path/to/miniconda3/envs/pm/

  data_dir:
    /path/to/my_dir/
  vcf_file:
    /path/to/my_dir/file.vcf
  query_file:
    /path/to/my_dir/queryIDs.txt
  out_dir:
   /path/to/my_dir/segments/
  ```
#### 3. Create new config file for slicing into segments. (See below for more information)
- create a new file `./my_dir/<config_file>.yaml`
- follow example at[`./cpp/configs/config_ex.yaml`](https://github.com/kristen-schneider/precision-medicine/blob/main/data/example_data/config_ex.yaml). Modify the following options to reflect appropriate file paths.
  ```
  vcf_file=/path/to/data_directory/file.vcf

  map_file=/path/to/data_directory/file.map

  out_dir=/path/to/data_directory/segments/

  out_base_name=<output_name>
  ```
#### 4. Running with snakemake
`snakemake -c1`

### More information about making yaml and config files.
#### yaml file:
`data_dir`: contains `file.vcf`, `file.map`, `and queryIDs.txt`.<br>
`query_file`: contains a list of query sample IDs. One ID per line.<br>
`out_dir`: a subdirectory of `data_dir` which will contain all intermediate segment files.<br>
#### config file:
`map_file`: a genetic map for the data (contains chromosome information). [HapMap genetic maps in cM units from Beagle](https://bochet.gcc.biostat.washington.edu/beagle/genetic_maps/plink.GRCh38.map.zip)<br> Can use [ilash_analyzer](https://github.com/roohy/ilash_analyzer/blob/master/interpolate_maps.py) to help create map files.<br>
`out_dir`: a subdirectory of `data_dir` which will contain all intermediate segment files.<br>
`out_base_name`: used for naming scheme of all intermediate segment files.

