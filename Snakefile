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
		f"{config.bin_dir}/slice-vcf",
                f"{config.segments_out_dir}/segments.vcf.done", 
		f"{config.bin_dir}/encode-vcf", 
		f"{config.segments_out_dir}/segments.encoding.done"


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
		config_file=f"{config.configs_dir}/sample.config"
	output:
		done=f"{config.segments_out_dir}/segments.encoding.done"
	message:
		"Executing--encode vcf slices..."
	shell:
		"for vcf_f in {config.segments_out_dir}/*.vcf; do" \
		"	filename=$(basename $vcf_f);" \
                "       seg_name=${{filename%.*}};" \
		"	./{input.bin} {input.config_file} $vcf_f {config.segments_out_dir}/${{seg_name}}.encoding > {output.done};" \
		"done" \
		" && touch {output.done}"

