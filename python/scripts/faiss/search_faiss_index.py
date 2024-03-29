import os
from os.path import basename
import sys
import argparse
import numpy as np
import faiss

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('--idx', type=str)
    parser.add_argument('--emb_dir', type=str)
    parser.add_argument('--emb_ext', type=str, default='.emb')
    parser.add_argument('--k', type=int, default=20)
    parser.add_argument('--database_samples', type=str)
    parser.add_argument('--query_samples', type=str)
    parser.add_argument('--out_dir', type=str)
    parser.add_argument('--pedigree', type=int, default=0)

    return parser.parse_args()
def main():
    args = parse_args()
    idx = args.idx
    emb_dir = args.emb_dir
    k = args.k
    db_samples = args.database_samples
    query_samples = args.query_samples
    out_dir = args.out_dir
    emb_ext = args.emb_ext
    pedigree = args.pedigree    

    # read query and database samples
    query_samples_list = read_samples(query_samples)
    database_samples_list = read_samples(db_samples)

    print('Searching index for: {}'.format(idx))
    base = basename(idx)
    chrm = base.split('.')[0]
    segment = base.split('.')[1]

    # get embeddings for segment
    embedding_file = emb_dir + chrm + '.' + segment + '.' + emb_ext
    db_embeddings_dict = read_embeddings(embedding_file, database_samples_list, pedigree)
    q_embeddings_dict = read_embeddings(embedding_file, query_samples_list, pedigree)
    
    # open results file and clear contents
    results_file = out_dir + chrm + '.' + segment + '.knn'
    open(results_file, 'w').close()

    # search faiss index for each query sample
    for query_sample in query_samples_list:
        # get haplotype names for query sample
        query_sample_embedding_0 = q_embeddings_dict[query_sample+'_0']
        query_sample_embedding_1 = q_embeddings_dict[query_sample+'_1']
        # search faiss index
        D, I = search_faiss_index(idx, query_sample_embedding_0, k)
        # write results to file
        write_results(results_file, query_sample+'_0', db_embeddings_dict, D, I)
        # search faiss index
        D, I = search_faiss_index(idx, query_sample_embedding_1, k)
        # write results to file
        write_results(results_file, query_sample+'_1', db_embeddings_dict, D, I)

def search_faiss_index(index_file, query_sample_embedding, k):
    # read faiss index
    index = faiss.read_index(index_file)
    # search faiss index
    D, I = index.search(np.array([query_sample_embedding]), k)
    return D, I

def write_results(results_file, query_sample, segment_embeddings_dict, D, I):
    # write faiss search results to file
    o = open(results_file, 'a')
    o.write('Query: ' + query_sample + '\n')
    # write results
    # sample_hap, distance, index
    for i in range(len(I[0])):
        sample_hap = list(segment_embeddings_dict.keys())[I[0][i]]
        distance = D[0][i]
        index = I[0][i]
        o.write(sample_hap + '\t' + str(distance) + '\n')
    o.write('\n')
    o.close()

def read_embeddings(emb_file,
                    query_samples_list, 
                    pedigree):
    # return array of embeddings
    embeddings = {}

    # open embedding file
    for line in open(emb_file, 'r'):
        # split line
        line = line.split(' ')
        # get segment name
        sample_hap = line[0].split()[0]
    
        if pedigree == 1:
            sample_ID = '_'.join(sample_hap.split('_')[0:2])
        else:
            # get segment name
            sample_ID = sample_hap.split('_')[0]        

        # check if segment is in database
        if sample_ID not in query_samples_list:
            continue
        # get segment embedding
        segment_embedding = np.array([float(i) for i in line[1:]])
        # append to embeddings
        embeddings[sample_hap] = segment_embedding
    return embeddings

def read_samples(samples):
    # return list of query samples
    query_samples_list = []
    for line in open(samples, 'r'):
        query_samples_list.append(line.strip())
    return query_samples_list

if __name__ == '__main__':
    main()
