#include "utils.hpp"

#include <fstream>
#include <iostream>

std::vector<Point> coordTable;

int* load_file(std::string const& filename, std::vector<int>& S,
	std::vector<int>& sizes) {
	std::ifstream fileStream(filename);
	if (!fileStream.is_open()) {
		std::cout << "Couldn't open file\n";
		return nullptr;
	}

	int n, m, k;
	fileStream >> n >> m >> k;
	int tmp;
	for (int i = 0; i < m; ++i) {
		fileStream >> tmp;
		S.push_back(tmp);
	}
	for (int i = 0; i < n; ++i) {
		fileStream >> tmp;
		sizes.push_back(tmp);
	}
	int* weights;
	weights = new int[n*n];
	for (int i = 0; i < n*n; ++i) {
		fileStream >> tmp;
		weights[i] = tmp;
	}
	fileStream.close();
	S.push_back(m);
	S.push_back(n);
	S.push_back(k);
	return weights;
}


void createCoordTable(int total) {
	coordTable = std::vector<Point>(total);
	int x = 0;
	int y = 0;
	int i = 0;
	coordTable[i++] = Point(x, y);
	while (true) {
		while (x < -1 * y + 1) {
			coordTable[i++] = Point(++x, y);
			if (i >= total) return;
		}
		while (y < x) {
			coordTable[i++] = Point(x, ++y);
			if (i >= total) return;
		}
		while (x > -1 * y) {
			coordTable[i++] = Point(--x, y);
			if (i >= total) return;
		}
		while (y > x) {
			coordTable[i++] = Point(x, --y);
			if (i >= total) return;
		}
	}
}

void printSolution(std::vector<Block> blockList) {
	printf("\n");
	int Nblocks = blockList.size();
	for (int i = 0; i < Nblocks; ++i) {
		printf("%d: ", i);
		Block b = blockList[i];
		for (int posIdx = b.firstIdInList; posIdx < b.firstIdInList + b.size; ++posIdx) {
			Point p = coordTable[posIdx];
			printf("(%2ld, %2ld) ", p.x, p.y);
		}
		printf("\n");
	}
}
