#include "algorithm.hpp"

void updateBlocks(std::vector<int> const& order, std::vector<Block>& blockList) {
    int s = 0;
    for (int i : order) {
        blockList[i].firstIdInList = s;
        s += blockList[i].size;
    }
}
