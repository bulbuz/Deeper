#pragma once

#include <SDL.h>
#include <fstream>
#include <string>
#include <iostream>
#include <string>
#include <math.h>
#include <vector>

#include "Utils.h"
#include "Tile.h"
#include "Texture.h"
#include "Player.h"

class Level {
public:
	Level(int id, SDL_Renderer* g_Renderer);
	void run();
	bool running;

private:
	void init();
	void render();
	void handle_Events();
	void update(double dt);

	int levelNumber;
	void load_Map(std::string fileName);
	void draw_Map();
	void lighting();
	
	Player player;
	Texture tiles;
	Tile map[MAP_HEIGHT][MAP_WIDTH];
	SDL_Renderer* renderer;
	std::vector<SDL_Rect> collidables;

	double dt;
};
