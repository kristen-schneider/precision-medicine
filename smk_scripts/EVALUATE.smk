from types import SimpleNamespace
#
config = SimpleNamespace(**config)

shell.prefix("""
. /opt/conda/etc/profile.d/conda.sh
conda activate pmed;
""")

import glob
from os.path import basename

rule all:
    input:
        f"{config.out_dir}svs_sample_results/write_summary.done",
        f"{config.out_dir}svs_sample_results/plot_summary.done"

# 1.0 write summmary data to be used for plotting
rule write_summary:
    input:
        sample_IDs=f"{config.out_dir}sample_IDs.txt",
        svs_results_dir=f"{config.out_dir}svs_sample_results/",
    output:
        write_summary=f"{config.out_dir}svs_sample_results/write_summary.done"
    message:
        "Writing a summary result file for plotting..."
    shell:
        "python {config.root_dir}python/scripts/decode/report_samples.py" \
	" --sample_IDs {input.sample_IDs}" \
	" --ss_sample_results_dir {input.svs_results_dir}" \
	" --out_dir {input.svs_results_dir};" \
	" touch {output.write_summary};" 

# 2.0 plot summmary data
rule plot_summary:
    input:
        write_summary=f"{config.out_dir}svs_sample_results/write_summary.done",
	relations=f"{config.out_dir}samples.relations",
        sample_IDs=f"{config.out_dir}sample_IDs.txt",
        svs_results_dir=f"{config.out_dir}svs_sample_results/"
    output:
        plot_summary=f"{config.out_dir}svs_sample_results/plot_summary.done"
    message:
        "Plotting summary results..."
    shell:
        "python {config.root_dir}python/scripts/decode/lump_relations.py" \
	" --relations {input.relations}" \
	" --samples {input.sample_IDs}" \
	" --data_dir {input.svs_results_dir};" \
	" touch {output.plot_summary};" 