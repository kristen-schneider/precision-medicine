#ifndef BUILDINDEX_H
#define BUILDINDEX_H

#endif //BUILDINDEX_H

#include <iostream>
#include <string>
#include <faiss/IndexFlat.h>

using namespace std;
using idx_t = faiss::Index::idx_t;

//template <class indexType>
//indexType buildIndex(indexType index, string encodedFile, int start, int lengthSegment, int numSamples);

faiss::IndexFlatL2 build_faiss_index_segments(string eFile, int start, int lengthSeg, int numS);
//faiss::IndexFlatIP build_faiss_index_segments_IP(string eFile, int start, int lengthSeg, int numS);
