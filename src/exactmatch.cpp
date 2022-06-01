#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>

#include "exactmatch.h"
#include "readEncoding.h"

using namespace std;

int exact_match_main(string encodedFile, string queriesFile, int start, int lengthQuery, int numVariants, int numSamples, int numQueries, int numSegments){
	
	// get queries from file
        //float* queries = read_queries(queriesFile, numVariants, numQueries);
	float* queries = read_queries_segment(queriesFile, start, numVariants, lengthQuery, numQueries);
	for(int q = 0; q < numQueries; q++){
		// one query at a time
		float* currQuery = new float[lengthQuery];
		for(int i = 0; i < (lengthQuery); i++){
			currQuery[i] = queries[q * lengthQuery + i];
		}
		cout << "Query " << q << endl;
		float* distArr = compute_one_queryEM(currQuery, encodedFile, start, lengthQuery, numVariants, numSamples, numQueries);

		//for (int s = 0; s < numSegments; s++){
		//	float* distArr = compute_one_query(currQuery, encodedFile, start, lengthQuery, numVariants, numSamples, numQueries);
		//}

		// sort distArr, keep indexes
		float* sortedDistArr = new float[numSamples];


		delete[] currQuery;
	}
	return 0;
}

float *compute_one_queryEM(float* query, string encodedFile, int start, int segLength, int numVariants, int numSamples, int numQueries){
	// ifstream to encoded file
        ifstream inFile;
        // open encoded file
        inFile.open(encodedFile);
        if ( !inFile.is_open() ) {
                cout << "Failed to open: " << encodedFile << endl;
        }

	// store index and distance in my own hashmap
	float* distArr = new float[numSamples];
        
	// read encoded file line by line
        string line;
        int lineCount = 0;
        if(inFile.is_open()){
                while(getline(inFile, line)){
                        string s;
                        float f;

			// convert string line to float array
                        float* singleVector = new float[segLength];
                        int i = 0;
			for (int c = start; c < start+segLength; c++){
                                s = line[c];
                                f = stof(s);
                                singleVector[i] = f;
				i ++;
                        }
			float singleDistance = exact_match(query, singleVector, segLength);
			distArr[lineCount] = singleDistance;
			lineCount ++;
		}
	}
	cout << "...exact match computations complete." << endl;

	// writing results
        cout << "...writing exact match results." << endl;
        ofstream outBruteForceFile;
        outBruteForceFile.open("/home/sdp/precision-medicine/data/txt/exactMatchResults." +to_string(start)+".txt");
        for (int i = 0; i < numSamples; i++){
                outBruteForceFile << i << "\t" << distArr[i] << endl;
        }
        outBruteForceFile.close();

	return distArr;
}


float exact_match(float* vec1, float* vec2, int segLength){

	float numMismatches = 0;
	for (int i = 0; i < segLength; i++){
		if(vec1[i] != vec2[i]){
			numMismatches++;
		}
	}
	return numMismatches;
}
