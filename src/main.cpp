#include <algorithm>
#include <numeric>
#include <iterator>
#include <iostream>
#ifdef RENDER
#include <SDL2/SDL.h>
#include "renderer.hpp"
#endif // RENDER
#include "utils.hpp"
#include "algorithms.hpp"

int main(int argc, char* argv[]) {
	std::string file;
	switch (argc) {
		case 1:
			file = "../data/ex_n10_m5.txt";
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
	int k, n, m;
	load_file(file, subset, sizes, &weights, &n, &m, &k);
	symmetrizeMatrix(&weights, n);

	printf("\n\n");
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			printf("%3d ", weights[n * i + j]);
		}
		printf("\n");
	}
	int sizesSum = 0;
	for (int i = 0; i < n; sizesSum += sizes[i++]);
	printf("Total size: %d\n", sizesSum);

	/* Order of the blocks */
	std::vector<int> order(n);
	std::iota(order.begin(), order.end(), 0);

	int subsetSum = 0;
	for (int s_i : subset) subsetSum += sizes[s_i];

	printf("Subset element sizes: %d \n", subsetSum);

	createCoordTable(sizesSum);

	BlockList blockList;
	int s = 0;
	for (int i : order) {
		blockList.push_back(Block(i, sizes[i], s));
		s += sizes[i];
	}
	int* distanceMatrix = new int[n*n];
	distanceMatrix[0] = 0;

	updateBlocks(order, blockList);
	updateDistances(blockList, distanceMatrix);

	long score;
	score = getScore(weights, distanceMatrix, subset, n, k);
	printf("Score = %ld\n", score);

#ifdef RENDER
	DisplayManager dm(sizesSum, &blockList);
	dm.initRenderer();
	dm.drawLoop();
#endif // RENDER

	delete[] weights;
	delete[] distanceMatrix;
	return 0;
}
