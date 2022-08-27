from types import SimpleNamespace
configfile: "config.yaml" # path to the config
config = SimpleNamespace(**config)

LD_LIBRARY_PATH = f"{config.conda_dir}/lib"
shell.prefix("""
set -euo pipefail;
export LD_LIBRARY_PATH=\"{LD_LIBRARY_PATH}\";
""".format(LD_LIBRARY_PATH=LD_LIBRARY_PATH))

rule all:
	input:
		f"{config.sample_IDs}",
		f"{config.bin_dir}/slice-vcf",
                f"{config.segments_out_dir}/segments.vcf.done", 
		f"{config.segments_out_dir}/segments.plink.done",
		f"{config.bin_dir}/encode-vcf", 
		f"{config.segments_out_dir}/segments.encoding.done"

rule sample_IDs:
	input:
		vcf=f"{config.vcf_file}"
	output:
		sampleIDs=f"{config.sample_IDs}"
	message:
		"Getting list of all sample IDs from VCF file..."
	shell:
		"bcftools query -l {input.vcf} > {output.sampleIDs}"

rule split_vcf_COMPILE:
	input:
        	slice_vcf=f"{config.src_dir}/slice_vcf.cpp",
		read_config=f"{config.src_dir}/read_config.cpp"
	output:
                bin=f"{config.bin_dir}/slice-vcf"
	message:
		"Compiling--slice vcf into segments..."
	shell:
                "g++ " \
		" {input.slice_vcf} " \
                " {input.read_config} " \
                " -I {config.include_dir}/" \
                " -lhts" \
                " -o {output.bin}"

rule split_vcf_EXECUTE:
	input:
		bin=f"{config.bin_dir}/slice-vcf",
		config_file=f"{config.configs_dir}/sample.config"
	output:
		done=f"{config.segments_out_dir}/segments.vcf.done"
	message: 
		"Executing--slice vcf into segments..."
	shell:
		"./{input.bin} {input.config_file} > {output.done}" \
		" && touch {output.done}"

rule plink_genome_IBD:
	input:
		vcf_done=f"{config.segments_out_dir}/segments.vcf.done"
	output:
		done=f"{config.segments_out_dir}/segments.plink.done"
	message:
		"Running plink on all encodings"
	shell:
		"for vcf_f in {config.segments_out_dir}/*.vcf; do" \
		"       filename=$(basename $vcf_f);" \
		"	seg_name=${{filename%.*}};" \
		"	plink --vcf $vcf_f --genome --out {config.segments_out_dir}/${{seg_name}} > {output.done};" \
		"done" \
		" && rm {config.segments_out_dir}/*.log" \
		" && rm {config.segments_out_dir}/*.nosex" \
		" && touch {output.done}"

rule encode_vcf_COMPILE:
	input:
		encode_vcf=f"{config.src_dir}/encode_vcf.cpp",
		read_config=f"{config.src_dir}/read_config.cpp", 
		map_encodings=f"{config.src_dir}/map_encodings.cpp",
		utils=f"{config.src_dir}/utils.cpp"
	output:
		bin=f"{config.bin_dir}/encode-vcf"
	message:
		"Compiling--encode vcf slices..."
	shell:
		"g++ " \
                " {input.encode_vcf} " \
                " {input.read_config} " \
		" {input.map_encodings} "\
		" {input.utils} " \
                " -I {config.include_dir}/" \
                " -lhts" \
                " -o {output.bin}"

rule encode_vcf_EXECUTE:
	input:
		bin=f"{config.bin_dir}/encode-vcf",
		sample_IDs=f"{config.sample_IDs}", 
		config_file=f"{config.configs_dir}/sample.config"
	output:
		done=f"{config.segments_out_dir}/segments.encoding.done"
	message:
		"Executing--encode vcf slices..."
	shell:
		"for vcf_f in {config.segments_out_dir}/*.vcf; do" \
		"	filename=$(basename $vcf_f);" \
                "       seg_name=${{filename%.*}};" \
		"	./{input.bin} {input.config_file} {input.sample_IDs} $vcf_f {config.segments_out_dir}/${{seg_name}}.encoding > {output.done};" \
		"done" \
		" && touch {output.done}"

