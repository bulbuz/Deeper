#pragma once

#define MAP_WIDTH 30
#define MAP_HEIGHT 20

#define SCALE 4
#define TILE_SIZE 8 * SCALE

#define WINDOW_WIDTH TILE_SIZE * MAP_WIDTH
#define WINDOW_HEIGHT TILE_SIZE * MAP_HEIGHT

struct Vec2 {
	double x;
	double y;
};

struct Dir {
	bool left;
	bool right;
	bool up;
	bool down;
};