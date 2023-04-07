#include "structures.hpp"

/* Manhatan distance between p1 and p2 */
int distance(Point const& p1, Point const& p2) {
	return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

Block::Block(int id, int size, int firstId) {
	this->id = id;
	this->size = size;
	this->firstIdInList = firstId;
};

void Block::getFirstIdAndSize(int* fId, int* size) {
	*fId = this->firstIdInList;
	*size = this->size;
}
