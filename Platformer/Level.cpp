#include "Level.h"

Level::Level(int id, SDL_Renderer* g_Renderer) {
	levelNumber = id;

	renderer = g_Renderer;
	running = 1;
	gravity = 9;
}

void Level::run() {
	init();

	// main 
	double dt = 0;
	Uint32 desiredDelta = 1000 / FPS;
	Uint64 now = SDL_GetPerformanceCounter();
	Uint64 last = 0;
	while (running) {
		Uint32 start = SDL_GetTicks();
		last = now;
		now = SDL_GetPerformanceCounter();

		dt = (double)((now - last) / (double)SDL_GetPerformanceFrequency());

		handle_Events();
		update(dt);
		render();

		Uint32 delta = SDL_GetTicks() - start;
		if (delta < desiredDelta) {
			SDL_Delay(desiredDelta - delta);
		}
	}

}

void Level::init() {
	tiles.load_TextureFromFile(renderer, "res/tiles.png");
	load_Map("res/map" + std::to_string(levelNumber) + ".txt");

	// temporary (no anim)
	SDL_Rect player_Dim{ 0, 0, TILE_SIZE, TILE_SIZE * 2 };
	player.init(&player_Dim);
	player.load_Texture(renderer, "res/player.png"); 
}

void Level::update(double dt) {
	player.update(dt);
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

			if (event.key.keysym.sym == SDLK_d) {
				player.dir.right = 1;
			}

			if (event.key.keysym.sym == SDLK_a) {
				player.dir.left = 1;
			}
		}

		if (event.type == SDL_KEYUP) {
			if (event.key.keysym.sym == SDLK_d) {
				player.dir.right = 0;
			}

			if (event.key.keysym.sym == SDLK_a) {
				player.dir.left = 0;
			}
		}
	}
}

void Level::render() {
	// clear screen
	SDL_SetRenderDrawColor(renderer, 23, 19, 33, 255);

	SDL_RenderClear(renderer);

	draw_Map();
	player.render(renderer);

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
