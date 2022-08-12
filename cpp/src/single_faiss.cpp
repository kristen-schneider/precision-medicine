#include <faiss/IndexFlat.h>
#include <faiss/IndexHNSW.h>
#include <iostream>

#include "buildIndex.h"
#include "searchIndex.h"
#include "utils.h"

// 64-bit int
using idx_t = faiss::Index::idx_t;
using namespace std;

int main(int argc, char* argv[]){

	cout << "Running FAISS on one segment encoding file." << endl;
	
	string encodedTXT = argv[1];
	string queriesTXT = argv[2];
	int k = stoi(argv[3]);

	int encoded_dimensions[2];	// [num_samples, num_variants]
	int queries_dimensions[2];	// [num_queries, num_variants]
	get_dimensions(encodedTXT, encoded_dimensions);
	get_dimensions(queriesTXT, queries_dimensions);
	int num_samples = encoded_dimensions[0];
	int num_variants = encoded_dimensions[1];
	int num_queries = queries_dimensions[0];

	cout << "Number samples: " << num_samples << endl;
	cout << "Number variants: " << num_variants << endl;
	cout << "Number queries: " << num_queries << endl;
	


	cout << "Starting FAISS for " << encodedTXT << endl;

	cout << "Building index..." << endl;
	/*
	faiss::IndexHNSWFlat index = build_faiss_index(encodedTXT, \
                        num_variants, \
                        num_samples);
	*/
	faiss::IndexFlatL2 index = build_faiss_index(encodedTXT, \
			num_variants, \
			num_samples);

	cout << "Running search..." << endl;
	search(index, k, queriesTXT, \
		 	num_queries, \
			num_variants);	
		
}
