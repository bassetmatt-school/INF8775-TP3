#ifndef TP3_UTILS_HEADER
#define TP3_UTILS_HEADER

#include <string>
#include <vector>
#include <deque>
#include "structures.hpp"

int* load_file(std::string const& filename, std::vector<int>& S, std::vector<int>& sizes);

void createCoordTable(std::deque<Point>& coords, int total);

#endif /* TP3_UTILS_HEADER */
