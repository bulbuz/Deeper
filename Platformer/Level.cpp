#include "Level.h"

Level::Level(int id, SDL_Renderer* g_Renderer) {
	levelNumber = id;

	renderer = g_Renderer;
	running = 1;
}

void Level::run() {
	init();

	while (running) {
		Uint64 start = SDL_GetPerformanceCounter();

		handle_Events();
		update();
		render();

		Uint64 end = SDL_GetPerformanceCounter();
		double elapsed = (end - start) / (double)SDL_GetPerformanceFrequency();
		start = end;

		std::cout << "FPS: " << std::to_string(1 / elapsed) << "\n";
	}
}

void Level::init() {
	tiles.load_TextureFromFile(renderer, "res/tiles.png");
	load_Map("res/map" + std::to_string(levelNumber) + ".txt");
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
	SDL_SetRenderDrawColor(renderer, 24, 20, 37, 255);
	SDL_RenderClear(renderer);

	draw_Map();

	// present buffer
	SDL_RenderPresent(renderer);
}

void Level::load_Map(std::string fileName) {
	std::fstream fin;
	fin.open(fileName);

	if (fin.is_open()) {
		for (int i = 0; i < MAP_HEIGHT; ++i) {
			for (int j = 0; j < MAP_WIDTH; ++j) {
				int id;
				fin >> id;
				map[i][j] = Tile();
				if (id != -1) {
					SDL_Rect dim{ (id / 32) * TILE_SIZE, (id % 32) * TILE_SIZE, TILE_SIZE, TILE_SIZE };
					map[i][j].init(&dim);
				}
				map[i][j].setId(id);
			}
		}
	} else {
		std::cerr << "Couldn't open map!" << std::endl;
	}
}

void Level::draw_Map() {
	for (int i = 0; i < MAP_HEIGHT; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			if (map[i][j].getId() != -1) {
				tiles.render(renderer, j * TILE_SIZE, i * TILE_SIZE, &map[i][j].hitbox);
			}
		}
	}
}
