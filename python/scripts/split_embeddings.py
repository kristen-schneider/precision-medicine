import argparse
from os.path import basename
import numpy as np

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument('--emb_dir', type=str)
    parser.add_argument('--all_emb', type=str)    
    return parser.parse_args()


def main():
    # reading embedding file with all segments
    # and write out to segment files
    args = parse_args()
    emb_dir = args.emb_dir
    all_emb = args.all_emb
    chrm = basename(all_emb).split('.')[0]
    #print(chrm)
    read_embedding_file(emb_dir, all_emb, chrm)

def read_embedding_file(embeddings_dir, embeddings_all, chrm):
    with open(embeddings_all, 'r') as f:
        for line in f:
            L = line.strip().split()
            sample = L[0]
            segment = L[1]
            embedding = L[2:]
            # append sample and embedding to segment file
            segment_file = embeddings_dir + chrm + '.segment' + segment + '.emb'
            with open(segment_file, 'a') as f:
                f.write(sample + ' ' + ' '.join(embedding) + '\n')


if __name__ == '__main__':
    main()