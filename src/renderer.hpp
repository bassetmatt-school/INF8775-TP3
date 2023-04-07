#ifndef TP3_RENDERER_HEADER
#define TP3_RENDERER_HEADER

#include <vector>
#include <tuple>
#include <SDL2/SDL.h>
#include "structures.hpp"
#include "utils.hpp"

using ColorList = std::vector<SDL_Color>;

class DisplayManager {
private:
	int maxCoord;
	int blockSize;
	BlockList* p_blockList;
	ColorList colList;
public:
	DisplayManager(int size, BlockList* p_blockList);
	void initRenderer();
	void drawLoop();
private:
	void getColors();
	void drawBlocks();
};
#endif /* TP3_RENDERER_HEADER */
