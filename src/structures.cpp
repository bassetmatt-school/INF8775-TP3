#include "structures.hpp"

/* Manhatan distance between p1 and p2 */
int distance(Point const& p1, Point const& p2) {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}