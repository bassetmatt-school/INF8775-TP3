#ifndef TP3_ALGORITHM_HEADER
#define TP3_ALGORITHM_HEADER

#include <vector>
#include "structures.hpp"

void updateBlocks(std::vector<int> const& order, std::vector<Block>& blockList);

void updateDistances(std::vector<Block> const& blockList, int* distanceMatrix);

long getScore(int* weights, int* distanceMatrix, std::vector<int> const& subset, int n, int k);

#endif //  TP3_ALGORITHM_HEADER
