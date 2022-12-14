#include "Level.h"
#include <algorithm>

Level::Level(int id, SDL_Renderer* g_Renderer) {
	levelNumber = id;

	renderer = g_Renderer;
	running = 1;
	dt = 0.0;
}

void Level::run() {
	init();

	// main 
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
	for (int i = 0; i < MAP_HEIGHT; ++i) {
		for (int j = 0; j < MAP_WIDTH; ++j) {
			if (map[i][j].getId() == -1)
				continue;

			bool ok = 0;
			if (i > 0) {
				if (map[i - 1][j].getId() == -1) {
					ok = 1;
				}
			}
			if (j > 0) {
				if (map[i][j - 1].getId() == -1) {
					ok = 1;
				}
			}

			if (i < MAP_HEIGHT - 1) {
				if (map[i + 1][j].getId() == -1) {
					ok = 1;
				}
			}
			if (j < MAP_WIDTH - 1) {
				if (map[i][j + 1].getId() == -1) {
					ok = 1;
				}
			}

			// add tile to collidables list if edge
			if(ok)
				collidables.push_back(map[i][j].hitbox); 
		}
	}
}

void Level::update(double dt) {
	player.update(dt, collidables);
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

			if (event.key.keysym.sym == SDLK_SPACE) {
				player.jump = 1;
			}
			if (event.key.keysym.sym == SDLK_r) {
				player.reset = 1;
			}
		}
		if (event.type == SDL_KEYUP) {
			if (event.key.keysym.sym == SDLK_d) {
				player.dir.right = 0;
			}

			if (event.key.keysym.sym == SDLK_a) {
				player.dir.left = 0;
			}

			if (event.key.keysym.sym == SDLK_SPACE) {
				player.jump = 0;
			}
		}
	}
}

void Level::lighting() {
	// do some shadow stuff
	SDL_Rect shadow{0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
	SDL_RenderFillRect(renderer, &shadow);

	int rect_radius = 96 * 3;
	SDL_Rect player_light{player.pos.x - (rect_radius / 2) + (player.hitbox.w / 2), player.pos.y - (rect_radius / 2) + (player.hitbox.h / 4), rect_radius,  rect_radius};

	int xMid = player_light.w / 2;
	int yMid = player_light.h / 2;
	double radius = player.pos.x - player_light.x;
	int pixel_size = 8;
	for (int i = 0; i < player_light.h / pixel_size; ++i) {
		for (int j = 0; j < player_light.w / pixel_size; ++j) {
			double dist = (double)sqrt(pow(j * pixel_size - yMid, 2) + pow(i * pixel_size - xMid, 2));
			if (dist <= radius) {
				SDL_Rect pixel{player_light.x + j * pixel_size, player_light.y + i * pixel_size, pixel_size, pixel_size};

				double dim_level = dist / radius;
				int alpha = std::min(round(2.0 * (1 / dim_level)), 10.0);
				SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
				SDL_SetRenderDrawColor(renderer, 255, 255, 255, alpha);
				SDL_RenderFillRect(renderer, &pixel);
			}
		}
	}
}

void Level::render() {
	// clear screen
	SDL_SetRenderDrawColor(renderer, 23, 19, 33, 255);
	SDL_RenderClear(renderer);

	// draw entities
	draw_Map();
	player.render(renderer);

	// do lighting thingy
	lighting();

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
				map[i][j].setId(id);

				if (id != -1) {
					SDL_Rect dim{j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE};
					map[i][j].sprite_sheet_location.x = (id / 32) * TILE_SIZE / SCALE;
					map[i][j].sprite_sheet_location.y = (id % 32) * TILE_SIZE / SCALE;
					map[i][j].init(dim);
				}
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
				Vec2 vec = map[i][j].sprite_sheet_location;
				SDL_Rect r{vec.x, vec.y, TILE_SIZE / SCALE, TILE_SIZE / SCALE};

				// renders the tile from the spritesheet
				tiles.render(renderer, map[i][j].hitbox.x, map[i][j].hitbox.y, &r, SCALE);
			}
		}
	}
}
