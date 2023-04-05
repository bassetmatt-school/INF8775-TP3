#ifndef TP3_UTILS_HEADER
#define TP3_UTILS_HEADER

#include <string>
#include <vector>
#include <deque>
#include "structures.hpp"

// TODO: Do better function
int* load_file(std::string const& filename, std::vector<int>& S, std::vector<int>& sizes);

extern std::vector<Point> coordTable;

void createCoordTable(int total);

void printSolution(std::vector<Block> blockList);
#endif /* TP3_UTILS_HEADER */
