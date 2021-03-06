#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>

#include "metrics.h"
#include "readEncoding.h"

using namespace std;

/*
 * compute euclidean distance
 * sqrt (sumN(v1-v2)^2)
 */
float euclidean_distance(float* vec1, float* vec2, int segLength){

	float eucDist = 0;
	float sum = 0;
	for (int i = 0; i < segLength; i++){
		float diff = vec1[i]-vec2[i];
		float diffSqrd = pow(diff, 2);
		sum += diffSqrd;
	}
	eucDist = sqrt(sum);
	return eucDist;
}

/*
 * counts number of mismatches betweeen two vectors 
 */
float mismatch(float* vec1, float* vec2, int segLength){

        float numMismatches = 0;
        for (int i = 0; i < segLength; i++){
                if(vec1[i] != vec2[i]){
                        numMismatches++;
                }
        }
        return numMismatches;
}
/*
 * counts number of mismatches betweeen two vectors
 */
float smart_mismatch(float* vec1, float* vec2, int segLength){

        float mismatchScore = 0;
        for (int i = 0; i < segLength; i++){
                if(vec1[i] != vec2[i]){
                        mismatchScore += abs(vec1[i] - vec2[i]);
                }
        }
        return mismatchScore;
}

/*
 * counts number of shared nonreference genotypes
 * so if they are both het or het and hom alt += one
 * the count of alleles where they share a non-refrence allele
 */
float sharedNRG(float* vec1, float* vec2, int segLength){
	float numNRG = 0;
	
	for (int i = 0; i < segLength; i++){
                if(vec1[i] != 0 && vec2[i] != 0){
                        numNRG++;
                }
        }

	return numNRG;
}

/*
 * counts number of shared nonreference genotypes
 * more weight if they are nonrefeernce and are different (het and homo alt += 2)
 * the count of alleles where they share a non-refrence allele
 */
float sharedNRGWeighted(float* vec1, float* vec2, int segLength){
	float numNRG = 0;
	
	for (int i = 0; i < segLength; i++){
                if(vec1[i] != 0 && vec2[i] != 0){
                        // how many alleles are they sharing?
			if (vec1[i] < vec2[i]){numNRG+=vec1[i];}
			else{numNRG+=vec2[i];}
			//if(vec1[i] == vec2[i]){ // nonreference and same genotype
			//	numNRG++;
			//}else{numNRG+=2;} // nonreference and different genotype
                }
        }

	return numNRG;
}
