#include "Game.h"

Game::Game() {
	if (!init()) {
		exit(EXIT_FAILURE);
	}
}

Game::~Game() {
	cleanup();
}
void Game::run() {
	world[0].run();
}

bool Game::init() {
	bool success = true;
	running = true;

	WINDOW_WIDTH = TILE_SIZE * MAP_WIDTH;
	WINDOW_HEIGHT = TILE_SIZE * MAP_HEIGHT;
	TITLE = "Deeper";

	window = nullptr;
	renderer = nullptr;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
		success = false;
	}

	if (IMG_Init(IMG_INIT_PNG) < 0) {
		std::cerr << "SDL_Error: " << IMG_GetError() << std::endl;
		success = false;
	}

	window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
		success = false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		std::cerr << "SDL_Error: " << SDL_GetError() << std::endl;
		success = false;
	}

	createWorld();

	return success;
}

void Game::createWorld() {
	// temporary world
	world.push_back(Level(1, renderer));
}

void Game::cleanup() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	IMG_Quit();
	SDL_Quit();
}
