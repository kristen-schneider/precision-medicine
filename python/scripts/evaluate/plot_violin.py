import matplotlib.pyplot as plt

def violin_plot(all_relations_scores, score_type, outpng):
	
    ordered_relations = [['self'],
    			['child', 'parent'],
    			['sibling'],
    			['grandchild', 'grandparent'],
                        ['niece-nephew', 'aunt-uncle'],
                        ['great-grandchild', 'great-grandparent'],
                        ['1-cousin'],
                        ['great-niece-nephew', 'great-aunt-uncle'],
                        ['1-cousin-1-removed'],
                        ['2-cousin'],
                        ['unrelated']]
    
    plot_data = {}
    fig, ax = plt.subplots(figsize=(20,15))
    
    for generation in ordered_relations:
        generation_data = []
        gen_lbl = "\n".join([rl for rl in generation])
        for relationship in generation:
            try:
                generation_data += all_relations_scores[relationship]
            except KeyError:
                generation_data = [0]
                print('no data for: ', relationship)
        plot_data[gen_lbl] = generation_data
    
    ax.violinplot([plot_data[col] for col in plot_data])
    ax.set_xticks(range(1,len(plot_data)+1))
    ax.set_xticklabels([col for col in plot_data], rotation=45)
    ax.set_xlabel('Relationship')
    ax.set_ylabel(score_type)
    ax.set_title('simulated pedgree', fontsize=20)
    
    for pc in ax.collections:
    	pc.set_facecolor('olivedrab')
    	pc.set_edgecolor('olivedrab')
    
    ax.spines['top'].set_visible(False)
    ax.spines['right'].set_visible(False)
    plt.savefig(outpng)
