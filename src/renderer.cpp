#include <cassert>
#include <cmath>
#include <fstream>
#include "renderer.hpp"

#define WINDOW_SIZE 945
SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;

DisplayManager::DisplayManager(int size, BlockList* p_blockList) {
	double approxSize = (std::sqrt(size) - 1) / 2;
	this->maxCoord = (int) std::round(approxSize);
	this->blockSize = WINDOW_SIZE / (2*this->maxCoord+1);
	this->p_blockList = p_blockList;
}

void DisplayManager::getColors() {
	std::string filename("./config/colors");
	std::ifstream fileStream(filename);
	if (!fileStream.is_open()) {
		std::cout << "Couldn't open file\n";
		return;
	}
	this->colList = ColorList(100);
	int r, g, b;
	for (int i = 0; i < 100; ++i) {
		fileStream >> r >> g >> b;
		colList[i] = SDL_Color{
			.r = (Uint8) r,
			.g = (Uint8) g,
			.b = (Uint8) b,
			.a = 255 };
	}
	fileStream.close();
}

void DisplayManager::initRenderer() {
	g_window = SDL_CreateWindow("TP3",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_SIZE, WINDOW_SIZE, 0);
	assert(g_window != NULL);
	g_renderer = SDL_CreateRenderer(g_window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	assert(g_renderer != NULL);
	this->getColors();
}

void DisplayManager::drawLoop() {
	bool running = true;
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case SDLK_ESCAPE:
							running = false;
							break;
					}
					break;
			}
		}
		SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
		SDL_RenderClear(g_renderer);
		this->drawBlocks();
		SDL_RenderPresent(g_renderer);
	}
}

void DisplayManager::drawBlocks() {
	int Nblocks = this->p_blockList->size();
	for (int i = 0; i < Nblocks; ++i) {
		int j0, s;
		(*p_blockList)[i].getFirstIdAndSize(&j0, &s);
		SDL_Color c = this->colList[i % 100];
		SDL_SetRenderDrawColor(g_renderer, c.r, c.g, c.b, c.a);
		for (int j = j0; j < j0 + s; ++j) {
			Point p = coordTable[j];
			SDL_Rect r;
			r.x = (p.x + this->maxCoord) * this->blockSize;
			r.y = (p.y + this->maxCoord) * this->blockSize;
			r.w = r.h = this->blockSize;
			SDL_RenderFillRect(g_renderer, &r);
		}
	}
}
