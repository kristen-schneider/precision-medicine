#include <cstdlib>
#include <iostream>
#include <cctype>
#include <fstream>
#include <string>

#include "read_encodings.h"

using namespace std;

// read queries file
float* read_queries(string queriestxt, int numVariants, int numQueries, const char delim){
        // path to queries file
        ifstream qFile;

        // open queries data (.txt file)
        qFile.open(queriestxt);
        if ( !qFile.is_open() ) {
                cout << "Failed to open: " << queriestxt << endl;
        }

	// to store all queries
        float* queriesArr = new float[numVariants * numQueries];
	int Q = 0;
	if(qFile.is_open()){
		string line;
                while(getline(qFile, line)){
			//iint segLength = line.length();
			string s;
                        float f;

                        // convert string line to float array
                        int i = 0;
                        size_t start;
                        size_t end = 0;
			if (delim == ' '){
                        	while ((start = line.find_first_not_of(delim, end)) != std::string::npos){
                                	end = line.find(delim, start);
                                	f = stof(line.substr(start, end - start));
                                	queriesArr[Q * numVariants + i] = f;
                                	i ++;
                        	}	
			}
			else{
				for (int c = 0; c < numVariants; c++){
                                	s = line[c];
                                	f = stof(s);
                                	queriesArr[Q * numVariants + c] = f;
                        	}
			}

			Q++;
		}
	}

        qFile.close();
        qFile.seekg(0);
        qFile.clear();
        return queriesArr;

}


// read queries file as segments
float* read_queries_segment(string queriestxt, int start, int numVariants, int segmentLength, int numQueries){
        // path to queries file
        ifstream qFile;

        // open queries data (.txt file)
        qFile.open(queriestxt);
        if ( !qFile.is_open() ) {
                cout << "Failed to open: " << queriestxt << endl;
        }

	// to store all queries
        float* queriesArr = new float[segmentLength * numQueries];
	
	int Q = 0;
	if(qFile.is_open()){
		string line;
                while(getline(qFile, line)){
			string s;
                        float f;
                        // convert string line to float array
			int i = 0;
                        for (int c = start; c < (start+segmentLength); c++){
                                s = line[c];
                                f = stof(s);
				queriesArr[Q * segmentLength + i] = f;
				i++;
                        }
			Q++;
		}
	}
	/*
	cout << "QUERY" << endl;
	for (int i = 0; i < segmentLength; i++){cout << queriesArr[i] << " ";}
	cout << endl;
	*/
        qFile.close();
        qFile.seekg(0);
        qFile.clear();
	/*
        cout << "SEGMENT LENGTH: " << segmentLength << endl;
	cout << "NUM QUERIES: " << numQueries << endl;
	for (int i = 0; i < (segmentLength * numQueries); i ++){
		cout << queriesArr[i];
	}
	*/
	return queriesArr;

}
