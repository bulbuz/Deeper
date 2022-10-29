#pragma once

#include <SDL.h>
#include <fstream>
#include <string>
#include <iostream>

#include "Utils.h"
#include "Tile.h"

class Level {
public:
	Level(int id, SDL_Renderer* g_Renderer);
	void run();
	bool running;

private:
	void init();
	void render();
	void handle_Events();
	void update();

	int levelNumber;
	void load_Map(std::string fileName);
	void draw_Map();
	
	Tile map[MAP_HEIGHT][MAP_WIDTH];
	SDL_Renderer* renderer;
};
