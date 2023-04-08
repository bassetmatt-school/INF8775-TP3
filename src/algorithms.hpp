#ifndef TP3_ALGORITHM_HEADER
#define TP3_ALGORITHM_HEADER

#include <vector>
#include "structures.hpp"

void updateBlocks(std::vector<int> const& order, BlockList& blockList);

void updateDistances(BlockList const& blockList, int* distanceMatrix);

long getScore(int* weights, int* distanceMatrix, std::vector<int> const& subset, int n, int k);

void randomizeOrder(std::vector<int>& order);

void twoSwap(std::vector<int>& order);

#endif //  TP3_ALGORITHM_HEADER
