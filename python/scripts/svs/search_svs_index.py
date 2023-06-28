# [imports]
import os
import pysvs
import argparse
import numpy as np
# [imports]

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('--idx_dir', type=str)
    parser.add_argument('--emb_dir', type=str)
    parser.add_argument('--emb_ext', type=str, default='.emb')
    parser.add_argument('--db_samples', type=str)
    parser.add_argument('--q_samples', type=str)
    parser.add_argument('--k', type=int, default=20)
    parser.add_argument('--out_dir', type=str)
    return parser.parse_args()

def main():
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

    for seg_idx in os.listdir(idx_dir):
        if seg_idx.endswith('_config'):
            print('Searching index for: {}'.format(seg_idx))
            base = seg_idx.split('_')[0]
            chrm = base.split('.')[0]
            segment = base.split('.')[1]
    
    
            # get embeddings for segment
            embedding_file = emb_dir + chrm + '.' + segment + '.' + emb_ext
            print('embedding file: ', embedding_file)
            db_embeddings_dict = read_embeddings(embedding_file, database_samples_list)
            q_embeddings_dict = read_embeddings(embedding_file, query_samples_list)
            #print(q_embeddings_dict)

            # open results file and clear contents
            results_file = out_dir + chrm + '.' + segment + '.knn'
            open(results_file, 'w').close()
            index = pysvs.Vamana(
                    os.path.join(idx_dir, base+'_config'),
                    pysvs.GraphLoader(os.path.join(idx_dir, base+'_graph')),
                    pysvs.VectorDataLoader(
                        os.path.join(idx_dir, base+'_data'), pysvs.DataType.float32
                        ),
                    pysvs.DistanceType.L2,
                    num_threads = 4,
                    )
            query_embeddings = []
            for q in query_samples_list:
                #print(q)
                query_sample_embedding_0 = q_embeddings_dict[q+'_0']
                query_sample_embedding_1 = q_embeddings_dict[q+'_1']
                query_embeddings.append(query_sample_embedding_0)
                query_embeddings.append(query_sample_embedding_1)
            queries = [np.array(e, dtype=np.float32) for e in query_embeddings]
            #I, D = index.search(query_sample_embedding_0, 10)
            #print(I, D)
            ## search faiss index for each query sample
            #for query_sample in query_samples_list:

def read_samples(samples):
    # return list of samples
    samples_list = []
    for line in open(samples, 'r'):
        samples_list.append(line.strip())
    return samples_list

def read_embeddings(gt_embedding_file, db_samples_list):
    # return array of embeddings
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
        if sample_ID not in db_samples_list:
            continue
        else:
            # get segment embedding
            segment_embedding = [float(i) for i in line[1:]]
            # append to embeddings
            #embeddings.append((sample_hap, segment_embedding))
            embedding_dict[sample_hap] = segment_embedding      
    # convert data to numpy array and reshape
    for sample in embedding_dict:
        np_dict[sample] = np.array(embedding_dict[sample], dtype=np.float32)
    return np_dict
    #np.vstack([data_array, embeddings[i][1]])
    #data_array = [np.array(i[1], dtype=np.float32) for i in embeddings]
    #data_array = np.array([i[1] for i in embeddings])
    #data_array = data_array.reshape(data_array.shape[0], data_array.shape[1])
    #return data_array

if __name__ == '__main__':
    main()