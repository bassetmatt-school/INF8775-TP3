#include <vector>
#include "coord.cpp"

class block {
public:
    int id;
    int size;
    std::vector<coord> coords;

    block(int a, int b) {
        this->id = a;
        this->size = b;
        // initialize vector ??
    };
};
