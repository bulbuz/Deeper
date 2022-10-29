#include "Level.h"

Level::Level(int id, SDL_Renderer* g_Renderer) {
	levelNumber = id;
	init();

	renderer = g_Renderer;
}

void Level::run() {
	init();

	while (running) {
		handle_Events();
		update();
		render();
	}
}

void Level::init() {
	load_Map("map" + std::to_string(levelNumber) + ".csv");
}

void Level::draw_Map() {
	for (int i = 0; i < MAP_HEIGHT; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			map[i][j].render(renderer);
		}
	}
}

void Level::update() {

}

void Level::handle_Events() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = 0;
		}

		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				running = 0;
			}
		}
	}
}

void Level::render() {
	// clear screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	draw_Map();

	// present buffer
	SDL_RenderPresent(renderer);
}

void Level::load_Map(std::string fileName) {
	std::fstream fin;

	puts(fileName.c_str());
	fin.open(fileName);
	std::string line;
	if (fin.is_open()) {
		int row = 0;
		while (std::getline(fin, line)) {
			int column = 0;
			for (char c : line) {
				if (c != ',') {
					map[row++][column++] = Tile();

					// initialize the tiles dimensions
					SDL_Rect dim{row * TILE_SIZE, column * TILE_SIZE, TILE_SIZE, TILE_SIZE};
					map[row][column].init(&dim);
				}
			}
		}
	} else {
		std::cerr << "Couldn't open map!" << std::endl;
	}
}
