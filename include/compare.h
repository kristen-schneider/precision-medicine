#ifndef COMPARE_H
#define COMPARE_H

#endif //COMPARE_H

#include <iostream>
#include <string>

using namespace std;

int compare_main(string eFile, string qFile, int start, int lenQuery, int numV, int numS, int numQ, int numSeg, string metric);
float* compute_one_query(float* q, string eFile, int start, int lenQUery, int numV, int numS, int numQ, string metric);
