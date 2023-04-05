#include <algorithm>
#include <deque>
#include <list>
#include <numeric>
#include <iterator>
#include <iostream>

#include "utils.hpp"
#include "algorithms.hpp"

int main(int argc, char* argv[]) {
	std::string file;
	switch (argc) {
		case 1:
			file = "./data/n1000_m500_V-8435325196.txt";
			break;
		case 2:
			file = argv[1];
			break;
		default:
			exit(1);
			break;
	}
	std::vector<int> subset;
	std::vector<int> sizes;
	int* weights;
	weights = load_file(file, subset, sizes);
	int k = subset[subset.size() - 1];
	subset.pop_back();
	int n = subset[subset.size() - 1];
	subset.pop_back();
	int m = subset[subset.size() - 1];
	subset.pop_back();
	printf("n = %d, m = %d, k = %d\n", n, m, k);
	// for (int i : subset) {
	// 	printf("%2d ", i);
	// }
	// printf("\n");
	// for (int i : sizes) {
	// 	printf("%2d ", i);
	// }
	// printf("\n");

	// for (int i = 0; i < n; ++i) {
	// 	for (int j = 0; j < n; ++j) {
	// 		printf("%3d ", weights[n * i + j]);
	// 	}
	// 	printf("\n");
	// }

	for (int i = 0; i < n; ++i) {
		for (int j = i; j < n; ++j) {
			weights[n * i + j] += weights[n * j + i];
			weights[n * j + i] = 0;
		}
	}
	// printf("\n\n");
	// for (int i = 0; i < n; ++i) {
	// 	for (int j = 0; j < n; ++j) {
	// 		printf("%3d ", weights[n * i + j]);
	// 	}
	// 	printf("\n");
	// }
	int total = 0;
	for (int i = 0; i < n; ++i) {
		total += sizes[i];
	}
	printf("total= %d", total);
	printf("\n");

	/* Order of the blocks */
	std::vector<int> order(n);
	std::iota(order.begin(), order.end(), 0);
	// for (int i : order) printf("%d|", i);
	// printf("\n");

	int sousEnsTot = 0;
	for (int i = 0; i < (int) subset.size(); i++) {
		sousEnsTot += sizes[subset[i]];
	}
	printf("sousTot= %d \n", sousEnsTot);
	createCoordTable(total);
	//print coords table
	// printf("size: %lu \n", coordTable.size());
	// for (int i = 0; i < (int) coordTable.size(); i++) {

	// 	printf("%d: %ld, %ld \n", i, coordTable[i].x, coordTable[i].y);
	// }
	std::vector<Block> blockList;
	int s = 0;
	for (int i : order) {
		blockList.push_back(Block(i, sizes[i], s));
		s += sizes[i];
	}
	int* distanceMatrix = new int[n*n];
	distanceMatrix[0] = 0;

	updateBlocks(order, blockList);
	updateDistances(blockList, distanceMatrix);
	// for (int i = 0; i < n; ++i) {
	// 	for (int j = 0; j < n; ++j) {
	// 		printf("%3d ", distanceMatrix[n * i + j]);
	// 	}
	// 	printf("\n");
	// }

	// printSolution(blockList);

	long score;
	score = getScore(weights, distanceMatrix, subset, n, k);
	printf("Score = %ld\n", score);

	delete[] weights;
	delete[] distanceMatrix;
	return 0;
}
