#include <faiss/IndexFlat.h>
#include <faiss/IndexHNSW.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <chrono>

#include "search_index.h"
#include "build_index.h"
#include "read_encodings.h"

/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */


// 64-bit int
using idx_t = faiss::Index::idx_t;
using namespace std::chrono;
using namespace std;

//void search(const faiss::IndexHNSWFlat &index, int k, string queriesTXT,\
//	       	int num_queries, int num_elements){
void search(const faiss::IndexFlatL2 &index, int k, string query_IDs, string query_data,\
	       	int num_queries, int num_elements, char delim){
	
	idx_t* I = new idx_t[k * num_queries];
	float* D = new float[k * num_queries];

	float* queries = make_queries_arr(query_data, query_IDs, delim, num_queries, num_elements); 
	//float* queries = read_queries(queriesTXT, num_elements, num_queries, delim); 
	
	auto start = high_resolution_clock::now();
	index.search(num_queries, queries, k, D, I);
	auto stop = high_resolution_clock::now();
	auto duration_search = duration_cast<microseconds>(stop - start);	
	cout << "TIME:search:" << duration_search.count() << endl;

	for (int i = 0; i < num_queries; i++){
		cout << "QUERY: " << i << endl;
		for (int j = 0; j < k; j++){
			cout << I[i * k + j] << "\t" << sqrt(D[i * k + j]) << endl;
		}
		cout << endl;
	}
	delete[] I;
	delete[] D;
}

/*
 * makes an array of all queries
 */
float* make_queries_arr(string query_data, string query_IDs, char delim, int num_queries, int num_elements){
	float* queries = new float[num_queries * num_elements];
	
	// make map of sample ID to sample encoding (embedding)
        map<string, float*> ID_query_map = make_ID_data_map(query_data, delim, num_elements);

        // read through query file (list of samples in database)
        // and pull those vectors from the map to add to index
        ifstream q_file_stream;
        q_file_stream.open(query_IDs);
        if (!q_file_stream.is_open()){
                cout << "Failed to open: " << query_IDs << endl;
                exit(1);
        }
        string line;
	int sample_i = 0;
        while (getline(q_file_stream, line)){
                // pull sample vector from map
                float* sample_vector = ID_query_map[line];
		// add all elements to query array
		for (int q = 0; q < num_elements; q++){
			queries[sample_i * num_elements + q] = sample_vector[q];
		}
		sample_i ++;
        }
        q_file_stream.close();

	return queries;
}

