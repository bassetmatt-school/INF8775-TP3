#ifndef TP3_RENDERER_HEADER
#define TP3_RENDERER_HEADER

#include <vector>
#include <tuple>
#include <SDL2/SDL.h>
#include "structures.hpp"
#include "utils.hpp"

// SDL_Window* g_window = NULL;
// SDL_Renderer* g_renderer = NULL;
using ColorList = std::vector<SDL_Color>;
class DisplayManager {
private:
	int maxCoord;
	int blockSize;
	bool renderLines = true;
	BlockList* p_blockList;
	bool blocksRenderered  = false;
public:
	ColorList colList;
	DisplayManager(int size, BlockList* p_blockList);
	void initRenderer();
	void drawLoop();
private:
	void getColors();
	void drawBlocks();
	void drawLines();
};
#endif /* TP3_RENDERER_HEADER */
