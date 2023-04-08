#include <fstream>
#include <iostream>
#include "utils.hpp"

PointList coordTable;

void load_file(
	std::string const& filename,
	std::vector<int>& subset,
	std::vector<int>& sizes,
	int** p_weights,
	int* p_n,
	int* p_m,
	int* p_k) {
	std::ifstream fileStream(filename);
	/* File fails to load (most likely wrong path) */
	if (!fileStream.is_open()) {
		printf("Couldn't open file %s.\n", filename.c_str());
		exit(1);
	}
	/* Reads m, n, k at the beginning of the file */
	int n, m, k;
	fileStream >> n >> m >> k;

	int tmp;
	/* Reads the m elements of the subset */
	for (int i = 0; i < m; ++i) {
		fileStream >> tmp;
		subset.push_back(tmp);
	}
	/* Reads the sizes of the n elements */
	for (int i = 0; i < n; ++i) {
		fileStream >> tmp;
		sizes.push_back(tmp);
	}
	/* Reads the weight matrix */
	int* weights = new int[n*n];
	for (int i = 0; i < n*n; ++i) {
		fileStream >> tmp;
		weights[i] = tmp;
	}
	fileStream.close();

	/* Updates pointer variables values */
	*p_weights = weights;
	*p_n = n; *p_m = m; *p_k = k;
}

void symmetrizeMatrix(int** p_weights, int n) {
	int* weights = *p_weights;
	for (int i = 0; i < n; ++i) {
		for (int j = i; j < n; ++j) {
			weights[n * i + j] += weights[n * j + i];
			weights[n * j + i] = weights[n * i + j];
		}
	}
	// int* new_weights = new int[(n*(n-1)) /2];
	// for (int i) {

	// }
	// delete[] weights;
	*p_weights = weights;
}

void createCoordTable(int total) {
	/* Pre-allocates vector memory space */
	coordTable = PointList(total);
	int x = 0, y = 0;
	int i = 0;
	coordTable[i++] = Point(x, y);
	/* Loops while going in larger circles. Stops when capacity is
	 * reached */
	while (true) {
		/* Goes right */
		while (x < -1 * y + 1) {
			coordTable[i++] = Point(++x, y);
			if (i >= total) return;
		}
		/* Goes up */
		while (y < x) {
			coordTable[i++] = Point(x, ++y);
			if (i >= total) return;
		}
		/* Goes left */
		while (x > -1 * y) {
			coordTable[i++] = Point(--x, y);
			if (i >= total) return;
		}
		/* Goes down */
		while (y > x) {
			coordTable[i++] = Point(x, --y);
			if (i >= total) return;
		}
	}
}

void printSolution(BlockList blockList, bool readable) {
	printf("\n");
	int Nblocks = blockList.size();
	for (int i = 0; i < Nblocks; ++i) {
		if (readable)
			printf("%d: ", i);
		Block b = blockList[i];
		for (int posIdx = b.firstIdInList; posIdx < b.firstIdInList + b.size; ++posIdx) {
			Point p = coordTable[posIdx];
			if (readable)
				printf("(%2ld, %2ld) ", p.x, p.y);
			else
				printf("%ld %ld", p.x, p.y);
		}
		printf("\n");
	}
}
