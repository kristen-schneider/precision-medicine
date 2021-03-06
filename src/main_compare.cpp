#include <iostream>

#include "buildIndex.h"
#include "compare.h"
#include "metrics.h"
#include "searchIndex.h"

using namespace std;
// 64-bit int
using idx_t = faiss::Index::idx_t;

// code to read VCF and write to encoded file is commented out
// only code for reading encoded file and performing FAISS will be run
int main(int argc, char* argv[]){
	
	// path to encoded file
        string encodingtxt = argv[1];           // file with encoded data
        string queriestxt = argv[2];            // file with query data

        int numVariants = atoi(argv[3]);        // number of variants (cols)
        int numSamples = atoi(argv[4]);         // number of samples (rows)
        int numQueries= atoi(argv[5]);          // number of queries sumbitted
        int k = atoi(argv[6]);                  // num nearest neighbors
        int segmentLength = atoi(argv[7]);      // length of one segment

	int numSegments = numVariants/segmentLength;
	cout << numSegments << endl;
	int metric = -1;
	
	
	/*
	cout << "------------------" << endl;
	cout << "Starting Euclidean Distance." << endl;
	int start_ed = 0;
	metric = 0;
	for (int i = 0; i < numSegments; i ++){
		cout << "\nSegment: " << start_ed << "-" << start_ed+segmentLength << endl;
		compare_main(encodingtxt, queriestxt, start_ed, segmentLength, numVariants, numSamples, numQueries, numSegments, metric);
		start_ed += segmentLength;
	}
	// last segment if differnt length	
	if (numVariants % segmentLength != 0){
		int lastSegmentLength = numVariants - (numSegments * segmentLength);
		cout << "\nSegment: " << start_ed << "-" << start_ed+lastSegmentLength << endl;
		compare_main(encodingtxt, queriestxt, start_ed, lastSegmentLength, numVariants, numSamples, numQueries, numSegments, metric);	
	}
	cout << "End of Euclidean Distance." << endl;
        cout << "------------------\n" << endl;
	

	cout << "------------------" << endl;
	cout << "Starting Counting Mismatches." << endl;
	int start_mm = 0;
	metric = 1;
	for (int i = 0; i < numSegments; i ++){
		cout << "\nSegment: " << start_mm << "-" << start_mm+segmentLength << endl;
		compare_main(encodingtxt, queriestxt, start_mm, segmentLength, numVariants, numSamples, numQueries, numSegments, metric);
		start_mm += segmentLength;
	}
	// last segment if differnt length	
	if (numVariants % segmentLength != 0){
		int lastSegmentLength = numVariants - (numSegments * segmentLength);
		cout << "\nSegment: " << start_mm << "-" << start_mm+lastSegmentLength << endl;
		compare_main(encodingtxt, queriestxt, start_mm, lastSegmentLength, numVariants, numSamples, numQueries, numSegments, metric);	
	}
	cout << "End of Counting Mismatches." << endl;
        cout << "------------------\n" << endl;


	cout << "------------------" << endl;
        cout << "Starting Counting SMART Mismatches." << endl;
        int start_smm = 0;
        metric = 2;
        for (int i = 0; i < numSegments; i ++){
                cout << "\nSegment: " << start_smm << "-" << start_smm+segmentLength << endl;
                compare_main(encodingtxt, queriestxt, start_smm, segmentLength, numVariants, numSamples, numQueries, numSegments, metric);
                start_smm += segmentLength;
        }
        // last segment if differnt length      
        if (numVariants % segmentLength != 0){
                int lastSegmentLength = numVariants - (numSegments * segmentLength);
                cout << "\nSegment: " << start_smm << "-" << start_smm+lastSegmentLength << endl;
                compare_main(encodingtxt, queriestxt, start_smm, lastSegmentLength, numVariants, numSamples, numQueries, numSegments, metric);   
        }
        cout << "End of Counting SMART Mismatches." << endl;
        cout << "------------------\n" << endl;



	cout << "------------------" << endl;
	cout << "Starting Counting Non-reference Genotypes." << endl;
        int start_nrg = 0;
        metric = 3;
        for (int i = 0; i < numSegments; i ++){
                cout << "\nSegment: " << start_nrg << "-" << start_nrg+segmentLength << endl;
                compare_main(encodingtxt, queriestxt, start_nrg, segmentLength, numVariants, numSamples, numQueries, numSegments, metric);
                start_nrg += segmentLength;
        }
        // last segment if differnt length      
        if (numVariants % segmentLength != 0){
                int lastSegmentLength = numVariants - (numSegments * segmentLength);
                cout << "\nSegment: " << start_nrg << "-" << start_nrg+lastSegmentLength << endl;
                compare_main(encodingtxt, queriestxt, start_nrg, lastSegmentLength, numVariants, numSamples, numQueries, numSegments, metric);
        }
        cout << "End of Counting Non-reference Genotypes." << endl;
        cout << "------------------\n" << endl;


	cout << "------------------" << endl;
        cout << "Starting Counting Non-reference Genotypes Weighted." << endl;
        int start_nrgw = 0;
        metric = 4;
        for (int i = 0; i < numSegments; i ++){
                cout << "\nSegment: " << start_nrgw << "-" << start_nrgw+segmentLength << endl;
                compare_main(encodingtxt, queriestxt, start_nrgw, segmentLength, numVariants, numSamples, numQueries, numSegments, metric);
                start_nrgw += segmentLength;
        }
        // last segment if differnt length      
        if (numVariants % segmentLength != 0){
                int lastSegmentLength = numVariants - (numSegments * segmentLength);
                cout << "\nSegment: " << start_nrgw << "-" << start_nrgw+lastSegmentLength << endl;
                compare_main(encodingtxt, queriestxt, start_nrgw, lastSegmentLength, numVariants, numSamples, numQueries, numSegments, metric);
        }
        cout << "End of Counting Non-reference Genotypes Weighted.." << endl;
        cout << "------------------\n" << endl;

*/

	return 0;
}
