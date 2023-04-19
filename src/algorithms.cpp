#include "algorithms.hpp"
#include "utils.hpp"

void updateBlocks(std::vector<int> const& order, BlockList& blockList) {
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

void updateDistances(BlockList const& blockList, int* distanceMatrix) {
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

void sizeSwap(std::vector<int>& order, int subsetSize, std::vector<int> sizes) {
	std::vector<std::pair<int, int>> tempOrder;
	std::vector<int>::iterator it1;
	std::vector<int>::iterator it2;

	for (int i=0; i < subsetSize; i++) {
		tempOrder.push_back(std::make_pair(order[i], sizes[order[i]]));
	}

	it1 = order.begin();
	it2 = order.begin();
	advance(it2, subsetSize);
	order.erase(it1, it2);

	std::sort(tempOrder.begin(), tempOrder.end(), [](auto& left, auto& right) {
		return left.second < right.second;
		});

	for (int i=subsetSize-1; i >= 0; i--) {
		order.insert(order.begin(), tempOrder[i].first);
	}
}

void sizeSwapNotSubset(std::vector<int>& order, int subsetSize, int setSize, std::vector<int> sizes) {
	std::vector<std::pair<int, int>> tempOrder;
	std::vector<int>::iterator it1;
	std::vector<int>::iterator it2;

	for (int i=subsetSize; i < setSize; i++) {
		tempOrder.push_back(std::make_pair(order[i], sizes[order[i]]));
	}

	it1 = order.begin();
	it2 = order.end();
	advance(it1, subsetSize);
	order.erase(it1, it2);

	std::sort(tempOrder.begin(), tempOrder.end(), [](auto& left, auto& right) {
		return left.second < right.second;
		});

	int notSubset = setSize - subsetSize;
	for (int i=0; i < notSubset; i++) {
		order.insert(order.end(), tempOrder[i].first);
	}
}

void putSubTogether(std::vector<int>& order,
	std::vector<int>& subset, int n) {
	std::list<int> tempOrder;

	for (int i=0; i<n;i++) {
		tempOrder.push_back(i);
	}

	for (int i : subset) {
		tempOrder.remove(i);
		tempOrder.push_front(i);
	}

	std::list<int>::iterator it;
	int i= 0;
	for (it=tempOrder.begin(); it!=tempOrder.end(); ++it) {
		order[i]= *it;
		i++;
	}
}
