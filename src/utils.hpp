#ifndef TP3_UTILS_HEADER
#define TP3_UTILS_HEADER

#include <string>
#include <vector>
#include "structures.hpp"

// TODO: Do better function
void load_file(
	std::string const& filename,
	/* Vector of indexes for m² bonus point subset */
	std::vector<int>& subset,
	std::vector<int>& sizes,
	/* Pointer towards the weight matrix */
	int** p_weights,
	int* p_n,
	int* p_m,
	int* p_k
);

/* Symmetrizes the weight matrix for more memory efficiency */
void symmetrizeMatrix(int** p_weights, int n);

/* Global variable linking indexes and coordinates */
extern PointList coordTable;

/* Creates the coodinate table. Here total is the sum of all weights */
void createCoordTable(int total);

/* Prints a solution. Either to expected output or in a more readbable way */
void printSolution(BlockList blockList, bool readable);
#endif /* TP3_UTILS_HEADER */
