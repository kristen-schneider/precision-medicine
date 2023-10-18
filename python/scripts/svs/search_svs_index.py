# [imports]
import os
import pysvs
import argparse
import numpy as np
# [imports]

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('--idx_dir', type=str, help='directory of all svs indexes')
    parser.add_argument('--emb_dir', type=str, help='directory of all embedding files')
    parser.add_argument('--emb_ext', type=str, default='.emb', help='extension for embedding files')
    parser.add_argument('--db_samples', type=str, help='list of all samples in database (haplotypes)')
    parser.add_argument('--q_samples', type=str, help='list of all query samples (haplotypes)')
    parser.add_argument('--k', type=int, default=20, help='k used for knn')
    parser.add_argument('--out_dir', type=str, help='directory to write svs search results')
    return parser.parse_args()

def main():
    # get arguments from argparse
    args = parse_args()
    idx_dir = args.idx_dir
    emb_dir = args.emb_dir
    k = args.k
    db_samples = args.db_samples
    query_samples = args.q_samples
    out_dir = args.out_dir
    emb_ext = args.emb_ext

    # read query and database samples
    query_samples_list = read_samples(query_samples)
    database_samples_list = read_samples(db_samples)
   
    # svs index creates 3 files that are kept in one directory, we want to search the '_config' one 
    for seg_idx in os.listdir(idx_dir):
        if seg_idx.endswith('_config'):
            base = seg_idx.split('_')[0]
            chrm = base.split('.')[0]
            segment = base.split('.')[1]
    
    
            # get embeddings for segment
            embedding_file = emb_dir + chrm + '.' + segment + '.' + emb_ext
            #print('embedding file: ', embedding_file)
            db_embeddings = read_embeddings(embedding_file, database_samples_list)
            q_embeddings = read_embeddings(embedding_file, query_samples_list)

            # open results file and clear contents
            results_file = out_dir + chrm + '.' + segment + '.knn'
            rf = open(results_file, 'w')
            # get svs index from config file
            index = pysvs.Vamana(
                    os.path.join(idx_dir, base+'_config'),
                    pysvs.GraphLoader(os.path.join(idx_dir, base+'_graph')),
                    pysvs.VectorDataLoader(
                        os.path.join(idx_dir, base+'_data'), pysvs.DataType.float32
                        ),
                    pysvs.DistanceType.L2,
                    num_threads = 4,
                    )
            
            # search index 
            # I : index
            # D : distance matrix
            I, D = index.search(q_embeddings, k)
            
            # for all queries in our list, write out results file for knn
            for query_idx in range(len(I)):
                q = I[query_idx]

                #query_idx = query_samples_list[query_result]
                #query_idx = q[0]
                query_line = 'Query: ' + query_samples_list[query_idx] + '\n'
                rf.write(query_line)
                
                for match_idx in range(len(q)):
                    m = q[match_idx]
                    match_line = query_samples_list[m] + '\t' + str(D[query_idx][match_idx]) + '\n'
                    rf.write(match_line)
                rf.write('\n')      
            rf.close()

def read_samples(samples):
    """
    return list of samples
    """
    samples_list = []
    for line in open(samples, 'r'):
        samples_list.append(line.strip())
    return samples_list

def read_embeddings(gt_embedding_file, db_samples_list):
    """
    return array of embeddings for all dabatase samples
    """
    embeddings = []
    embedding_dict = dict()
    np_dict = dict()

    # open embedding file
    for line in open(gt_embedding_file, 'r'):
        # split line
        line = line.strip().split(' ')
        # get segment name
        sample_hap = line[0].split()[0]
        sample_ID = sample_hap.split('_')[0]
        # check if segment is in database
        if sample_hap not in db_samples_list:
            continue
        else:
            # get segment embedding
            segment_embedding = [float(i) for i in line[1:]]
            # append to embeddings
            embeddings.append((sample_hap, segment_embedding))
            #embedding_dict[sample_hap] = segment_embedding      
    # convert data to numpy array and reshape
    #np.vstack([data_array, embeddings[i][1]])
    data_array = [np.array(i[1], dtype=np.float32) for i in embeddings]
    #data_array = np.array([i[1] for i in embeddings])
    #data_array = data_array.reshape(data_array.shape[0], data_array.shape[1])
    return data_array

if __name__ == '__main__':
    main()
