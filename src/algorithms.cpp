#include "algorithms.hpp"
#include "utils.hpp"

void updateBlocks(std::vector<int> const& order, std::vector<Block>& blockList) {
	int s = 0;
	for (int i : order) {
		blockList[i].firstIdInList = s;
		s += blockList[i].size;
	}
}

int blockDistance(Block const& b1, Block const& b2) {
	int dist = INT32_MAX;
	for (int i = b1.firstIdInList; i < b1.firstIdInList + b1.size; ++i) {
		for (int j = b2.firstIdInList; j < b2.firstIdInList + b2.size; ++j) {
			int d = distance(coordTable[i], coordTable[j]);
			if (d < dist) {
				dist = d;
			}
		}
	}
	return dist;
}

void updateDistances(std::vector<Block> const& blockList, int* distanceMatrix) {
	int Nblocks = blockList.size();
	for (int i = 0; i < Nblocks; ++i) {
		for (int j = i+1; j < Nblocks; ++j) {
			distanceMatrix[Nblocks * i + j] = blockDistance(blockList[i], blockList[j]);
		}
	}
}

long getScore(int* weights, int* distanceMatrix, std::vector<int> const& subset, int n, int k) {
	/* Weighted distances */
	long sumDist = 0;
	for (int i = 0; i < n; ++i) {
		for (int j = i+1; j < n; ++j) {
			sumDist += (long) weights[n * i + j] * distanceMatrix[n * i + j];
		}
	}
	int m = subset.size();
	bool bonus = true;
	for (int i = 0; i < m; ++i) {
		for (int j = i+1; j < m; ++j) {
			if (distanceMatrix[n * subset[i] + subset[j]] > k) {
				bonus = false;
			}
		}
	}
	long bonusPoints = bonus ? m*m : 0;
	return bonusPoints - sumDist;
}
