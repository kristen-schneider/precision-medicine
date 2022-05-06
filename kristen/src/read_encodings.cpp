#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "read_encodings.h"

using namespace std;

// need to convert this array workflow to vectors
vector<float> read_encoded_data(int numSamples){

	// path to encoding file
        string inFileString = "../../encoding.txt";
	ifstream inFile;
	// open encoded data (.txt file)
        inFile.open(inFileString);
	if ( !inFile.is_open() ) {
                cout << "Failed to open: " << inFileString << endl;
        }
	

	string line;	// to store line from file
	vector<float> vecOfFloats; // to store line as a vector of floats

	int s = 0;
	if (inFile.is_open()) {
		while (getline (inFile, line)) {
			
			//vecOfFloats.push_back(line);
			// to convert to array: https://stackoverflow.com/questions/43130421/convert-string-vector-to-float-vector-or-array
			//cohort_arr[s] = line;
			s += 1;
		}
		inFile.close();
	}
	return vecOfFloats;
}
