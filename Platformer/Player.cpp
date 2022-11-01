#include "Player.h"

Player::Player() {
	dir.right = 0;
	dir.left = 0;

	pos.x = 64;
	pos.y = 0;

	vel.x = 0;
	vel.y = 0;
}

void Player::update(double dt, std::vector<SDL_Rect> collidables) {
	// movement and gravity
	const double speed = 190.0;
	double gravity = 250.0;

	if (dir.right) {
		vel.x = speed * dt;
	} else if (dir.left) {
		vel.x = -speed * dt;
		pos.x -= ((double)vel.x * dt);
	} else {
		vel.x = 0;
	}

	// cap the vertical velocity
	vel.y = /*vel.y * dt +*/ dt * 0.5 * (gravity + gravity * dt);
	vel.y += gravity * dt;
	vel.y = std::min(2000.0, vel.y);

	SDL_Rect player_rectX = hitbox;
	SDL_Rect player_rectY = hitbox;
	player_rectX.x += vel.x;
	player_rectY.y += vel.y;

	double dx = vel.x;
	double dy = vel.y;
	for (SDL_Rect tile : collidables) {
		if (SDL_HasIntersection(&player_rectX, &tile)) {
			dx = 0;
			vel.x = 0;
		}

		if (SDL_HasIntersection(&player_rectY, &tile)) {
			if (vel.y >= 0) {
				dy = tile.y - (hitbox.y + hitbox.h);
				vel.y = 0;
			}
		}
	}
	std::cout << dx << " " << dy << "\n";

	pos.x += dx;
	pos.y += dy;

	hitbox.x = round(pos.x);
	hitbox.y = round(pos.y);
}