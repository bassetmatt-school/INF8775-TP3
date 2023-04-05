#include <iostream>
#include "utils.hpp"

int main(int argc, char* argv[]) {
	std::cout << "Test" << std::endl;
	std::string file;
	switch (argc) {
		case 1: file = "../data/ex_n10_m5.txt"; break;
		case 2: file = argv[1];
		default: exit(1); break;
	}
	std::vector<int> S;
	std::vector<int> sizes;
	int* weights;
	weights = load_file(file, S, sizes);
	int k = S[S.size() - 1];
	S.pop_back();
	int n = S[S.size() - 1];
	S.pop_back();
	int m = S[S.size() - 1];
	S.pop_back();
	printf("n = %d, m = %d, k = %d\n", n, m, k);
	for (int i : S) {printf("%2d ", i);}
	printf("\n");
	for (int i : sizes) {printf("%2d ", i);}
	printf("\n");

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			printf("%3d ", weights[n*i + j]);
		}
		printf("\n");
	}

	for (int i = 0; i < n; ++i) {
		for (int j = i; j < n; ++j) {
			weights[n*i + j] += weights[n*j + i];
			weights[n*j + i] = 0;
		}
	}
	printf("\n\n");
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			printf("%3d ", weights[n*i + j]);
		}
		printf("\n");
	}
	delete[] weights;
	return 0;
}
