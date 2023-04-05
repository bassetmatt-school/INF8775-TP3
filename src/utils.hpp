#ifndef TP2_UTILS_HEADER
#define TP2_UTILS_HEADER

#include <string>
#include <vector>
#include <deque>

#include "block.cpp"

int* load_file(std::string const& filename, std::vector<int>& S, std::vector<int>& sizes);

void createCoordTable(std::deque<coord>& coords, int total);

#endif // !TP2_UTILS_HEADER
