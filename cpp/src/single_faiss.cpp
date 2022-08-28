#include <faiss/IndexFlat.h>
#include <faiss/IndexHNSW.h>
#include <iostream>
#include <chrono>

#include "build_index.h"
#include "search_index.h"
#include "utils.h"

// 64-bit int
using idx_t = faiss::Index::idx_t;
using namespace std::chrono;
using namespace std;

int main(int argc, char* argv[]){

	cout << "Running FAISS on one segment encoding file." << endl;

	string database_IDs = argv[1];
	string database_data = argv[2];
	string query_IDs = argv[3];
	string query_data = argv[4];
	cout << argv[5] << endl;
	int k = stoi(argv[5]);
	// convert delim to char for differnt delims
	string s_delim = argv[6];
	char delim = '\0';
	if (s_delim == "space"){ delim = ' ';}


	int num_elements = count_length_input_vector(database_data, delim);
	int num_db_samples = count_num_samples(database_IDs);
	int num_q_samples = count_num_samples(query_IDs);

	cout << "Number database samples: " << num_db_samples << endl;
	cout << "Number query samples: " << num_q_samples << endl;
	cout << "Number vector elements: " << num_elements << endl;

	cout << "Building Index..." << endl;
	faiss::IndexFlatL2 faiss_index = build_index(database_IDs, database_data, delim, num_elements);
	cout << "Running search..." << endl;
	


//	cout << "Starting FAISS for " << database_file << endl;
//
//	auto start = high_resolution_clock::now();
//	cout << "Building index..." << endl;
//	/*
//	faiss::IndexHNSWFlat index = build_faiss_index(database_file, \
//                        num_variants, \
//                        num_samples);
//	*/
//	faiss::IndexFlatL2 index = build_faiss_index(database_file, \
//			num_variants, \
//			num_samples, 
//			delim);
//
//	cout << "Running search..." << endl;
//	search(index, k, query_file, \
//		 	num_queries, \
//			num_variants, \
//			delim);	
//		
//	auto stop = high_resolution_clock::now();
//	auto duration_file = duration_cast<microseconds> (stop - start);
//	cout << "TIME:file:" << duration_file.count() << endl;
}
