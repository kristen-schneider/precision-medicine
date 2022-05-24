#include <iostream>

#include "readVCF.h"
#include "utils.h"
//#include "readEncoding.h"
//#include "faiss_pm.h"

using namespace std;

// code to read VCF and write to encoded file is commented out
// only code for reading encoded file and performing FAISS will be run
int main(void){

	// MAKE CHANGES TO THESE VARIABLES 
	//const char* VCFfile = "/home/sdp/precision-medicine/data/vcf/ALL.chr14.shapeit2_integrated_snvindels_v2a_27022019.GRCh38.phased.vcf";

	// ...to be automated later...
	//int numSamples = 1000; // number of samples (rows) in encoding.txt
	//int numVariants = 100; // number of variants (cols) in encoding.txt
	//int numQueries = 3; // number of queries

	// path to encoded file
	//string encodingtxt = "/home/sdp/precision-medicine/data/encoded/ALLchr14.encoding.txt";
	//string queriestxt = "/home/sdp/precision-medicine/data/ALLchr14queries.txt";

	// create an array which will holds queries
//	float* xq = read_queries(queriestxt, numSamples, numVariants);

//	float seed[numVariants * numQueries] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f, 2.f}; 
//	float* xq = new float[numVariants * numQueries];
//	for (int i = 0; i < (numVariants * numQueries); i++) {
//        	xq[i] = seed[i];
//	}
	// DONE. start main.cpp.

	cout << "Start of encoding." << endl;

	cout << "Reading VCF file." << endl;
	sliceVCF();

//	cout << "Reading Encoded file." << endl;
//	float* xb = read_test(encodingtxt, numSamples, numVariants);
//	cout << "Done Reading Encoded file." << endl;
//	
//
//	cout << endl << "Starting FAISS." << endl;
//	ss(xb, xq, numSamples, numVariants, numQueries);
//	cout << "End of FAISS." << endl;

	return 0;
}