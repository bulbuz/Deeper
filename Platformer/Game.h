#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "GameObject.h"
#include "Player.h"
#include "Texture.h"
#include "Level.h"
#include "RoomManager.h"
#include "Utils.h"

class Game
{
public:
	Game();
	~Game();
	void run();

private:
	void createWorld();

	bool init();
	void cleanup();

	bool running;
	int WINDOW_WIDTH;
	int WINDOW_HEIGHT; 
	const char* TITLE;

	RoomManager room_Mgr;
	std::vector<Level> world;

	SDL_Window* window;
	SDL_Renderer* renderer;
};

