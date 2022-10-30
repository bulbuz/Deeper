#include "Level.h"
#include <algorithm>

Level::Level(int id, SDL_Renderer* g_Renderer) {
	levelNumber = id;

	renderer = g_Renderer;
	running = 1;
}

void Level::run() {
	init();

	// main 
	double dt = 0;
	Uint32 desiredDelta = 1000 / FPS;
	Uint64 now = SDL_GetPerformanceCounter();
	Uint64 last = 0;
	while (running) {
		last = now;
		now = SDL_GetPerformanceCounter();

		dt = (double)((now - last) / (double)SDL_GetPerformanceFrequency());

		handle_Events();
		update(dt);
		render();
	}
}

void Level::init() {
	tiles.load_TextureFromFile(renderer, "res/tiles.png");
	load_Map("res/map" + std::to_string(levelNumber) + ".txt");

	// temporary (no anim)
	SDL_Rect player_Dim{ 0, 0, TILE_SIZE, TILE_SIZE * 2 };
	player.init(player_Dim);
	player.load_Texture(renderer, "res/player.png"); 

	// get collidable tiles
	int cnt = 0;
	for (int i = 0; i < MAP_HEIGHT; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			if (map[i][j].getId() == -1)
				continue;

			if (i > 0) {
				if (map[i - 1][j].getId() == -1) {
					collidables.push_back(map[i - 1][j].hitbox);
				}
			}
			if (j > 0) {
				if (map[i][j - 1].getId() == -1) {
					collidables.push_back(map[i][j - 1].hitbox);
				}
			}

			if (i < MAP_HEIGHT - 1) {
				if (map[i + 1][j].getId() == -1) {
					collidables.push_back(map[i + 1][j].hitbox);
				}
			}
			if (j < MAP_WIDTH - 1) {
				if (map[i][j + 1].getId() == -1) {
					collidables.push_back(map[i][j + 1].hitbox);
				}
			}

		}
	}
}

void Level::update(double dt) {
	player.update(dt);

	for (auto tile : collidables) {
		if (SDL_HasIntersection(&tile, &player.hitbox)) {
			if (player.vel.y > 0) {
				player.pos.y = tile.y + player.hitbox.y;
			}
		}
		std::cout << tile.w << " " << tile.h << "\n";
	}
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
					SDL_Rect dim{i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE };

					map[i][j].sprite_sheet_location.x = (id / 32) * TILE_SIZE;
					map[i][j].sprite_sheet_location.y = (id % 32) * TILE_SIZE;
					map[i][j].init(dim);
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
				// initialize the clip in the spritesheet
				auto vec = map[i][j].sprite_sheet_location;
				SDL_Rect r{vec.x, vec.y, TILE_SIZE, TILE_SIZE};
				tiles.render(renderer, j * TILE_SIZE, i * TILE_SIZE, &r);
			}
		}
	}
}
