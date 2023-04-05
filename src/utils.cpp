#include <fstream>
#include <iostream>
#include "utils.hpp"

int* load_file(std::string const& filename, std::vector<int>& S, std::vector<int>& sizes){
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

void sort_order(std::vector<int>& order){
	int size = order.size();
	if (order[1] < order[size - 2]) return;
	std::vector<int> tmp(order);
	for (int i = 1; i < size - 1; ++i){
		order[i] = tmp[size - i - 1];
	}
}
