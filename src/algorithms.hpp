#ifndef TP3_ALGORITHM_HEADER
#define TP3_ALGORITHM_HEADER

#include <vector>
#include <list>
#include <utility>
#include <algorithm>
#include "structures.hpp"

void updateBlocks(std::vector<int> const& order, BlockList& blockList);

void updateDistances(BlockList const& blockList, int* distanceMatrix);

long getScore(int* weights, int* distanceMatrix, std::vector<int> const& subset, int n, int k);

void sizeSwap(std::vector<int>& order, int subsetSize, std::vector<int> sizes);

void sizeSwapNotSubset(std::vector<int>& order, int subsetSize, int setSize, std::vector<int> sizes);

void putSubTogether(std::vector<int>& order, std::vector<int>& subset, int n);

#endif //  TP3_ALGORITHM_HEADER
