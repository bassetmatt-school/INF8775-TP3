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
	bool p = false;
	switch (argc) {
		case 1:
			file = "../data/n1000_m500_V-8435325196.txt";
			break;
		case 2:
			file = argv[1];
			break;
		case 3:
			file = argv[1];
			p = *argv[2] - 48;
			break;
		default:
			fprintf(stderr, "Incorrect number of arguments\n");
			exit(1);
			break;
	}
	std::vector<int> subset;
	std::vector<int> sizes;
	int* weights;
	int* weightsSum;
	int k, n, m;
	load_file(file, subset, sizes, &weights, &weightsSum, &n, &m, &k);
	symmetrizeMatrix(&weights, n);

	int sizesSum = 0;
	for (int i = 0; i < n; sizesSum += sizes[i++]);

	/* Order of the blocks */
	std::vector<int> order(n);
	std::iota(order.begin(), order.end(), 0);

	int subsetSum = 0;
	for (int s_i : subset) subsetSum += sizes[s_i];

	createCoordTable(sizesSum);

	BlockList blockList;
	int s = 0;
	for (int i : order) {
		blockList.push_back(Block(i, sizes[i], s));
		s += sizes[i];
	}
	int* distanceMatrix = new int[n*n];
	distanceMatrix[0] = 0;


	//**********first in numerical order*********
	updateBlocks(order, blockList);
	updateDistances(blockList, distanceMatrix);
	long score;
	score = getScore(weights, distanceMatrix, subset, n, k);
	printf("\n");
	if (!p)
		printf("%ld\n", score);
	else
		printSolution(blockList, false);

	std::vector<int> tempOrder;

	//********putting subset together at the center********
	tempOrder = order;
	putSubTogether(tempOrder, subset, n);

	updateBlocks(tempOrder, blockList);
	updateDistances(blockList, distanceMatrix);

	long tempScore;
	tempScore = getScore(weights, distanceMatrix, subset, n, k);

	if (checkSolution(tempScore, score)) {
		//printf("subset grouped: Score = %ld\n", tempScore);
		order= tempOrder;
		if (!p)
			printf("%ld\n", score);
		else
			printSolution(blockList, false);
	}

	//******ordering elements in the subset based on sizes*****
	tempOrder = order;
	sizeSwap(tempOrder, m, sizes);


	updateBlocks(tempOrder, blockList);
	updateDistances(blockList, distanceMatrix);
	tempScore = getScore(weights, distanceMatrix, subset, n, k);

	if (checkSolution(tempScore, score)) {
		//printf("subset in order: Score = %ld\n", tempScore);
		order= tempOrder;
		if (!p)
			printf("%ld\n", score);
		else
			printSolution(blockList, false);
	}

	//*****ordering elements not in the subset******
	tempOrder = order;
	sizeSwapNotSubset(tempOrder, m, n, sizes);


	updateBlocks(tempOrder, blockList);
	updateDistances(blockList, distanceMatrix);
	tempScore = getScore(weights, distanceMatrix, subset, n, k);


	if (checkSolution(tempScore, score)) {
		//printf("2 sections in order: Score = %ld\n", tempScore);
		order= tempOrder;
		if (!p)
			printf("%ld\n", score);
		else
			printSolution(blockList, false);
	}





#ifdef RENDER
	DisplayManager dm(sizesSum, &blockList);
	dm.initRenderer();
	dm.drawLoop();
#endif // RENDER

	delete[] weights;
	delete[] distanceMatrix;
	return 0;
}
