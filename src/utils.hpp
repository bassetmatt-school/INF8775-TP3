#ifndef TP3_UTILS_HEADER
#define TP3_UTILS_HEADER

#include <string>
#include <vector>
#include "structures.hpp"

// TODO: Do better function
int* load_file(std::string const& filename, std::vector<int>& S, std::vector<int>& sizes);

extern PointList coordTable;

void createCoordTable(int total);

void printSolution(BlockList blockList);
#endif /* TP3_UTILS_HEADER */
