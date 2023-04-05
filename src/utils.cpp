#include "utils.hpp"

#include <fstream>
#include <iostream>

std::vector<Point> coordTable;

int* load_file(std::string const& filename, std::vector<int>& S,
	std::vector<int>& sizes) {
	std::ifstream file_stream(filename);
	if (!file_stream.is_open()) {
		std::cout << "Couldn't open file\n";
		return nullptr;
	}

	int n, m, k;
	file_stream >> n >> m >> k;
	int tmp;
	for (int i = 0; i < m; ++i) {
		file_stream >> tmp;
		S.push_back(tmp);
	}
	for (int i = 0; i < n; ++i) {
		file_stream >> tmp;
		sizes.push_back(tmp);
	}
	int* weights;
	weights = new int[n*n];
	for (int i = 0; i < n*n; ++i) {
		file_stream >> tmp;
		weights[i] = tmp;
	}
	file_stream.close();
	S.push_back(m);
	S.push_back(n);
	S.push_back(k);
	return weights;
}

int distance(int x1, int y1, int x2, int y2) {
	int d = abs(x2 - x1) + abs(y2 - y1);
	return d;
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
