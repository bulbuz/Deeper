#pragma once

#define MAP_WIDTH 30
#define MAP_HEIGHT 20

#define SCALE 4
#define TILE_SIZE 8 * SCALE

#define FPS 60

#define BLACK (0, 0, 0)
#define WHITE (255, 255, 255)

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