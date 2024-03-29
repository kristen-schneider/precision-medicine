#ifndef READENCODINGS_H
#define READENCODINGS_H

#endif //READENCODINGS_H

#include <cstdlib>
#include <iostream>
#include <string> 

using namespace std;

float* read_encodings(string encodingtxt, int numSamples, int numVariants);
float* read_queries(string queriestxt, int segLength, int numQueries, const char delim);
float* read_queries_segment(string queriestxt, int start, int numVariants, int segmentLength, int numQueries);
