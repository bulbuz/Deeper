#include "Player.h"

Player::Player() {
	dir.right = 0;
	dir.left = 0;

	pos.x = 500;
	pos.y = 0;

	vel.x = 0;
	vel.y = 0;

	ready_to_jump = 0;
	jump = 0;
	
	reset = 0;
}

void Player::update(double dt, std::vector<SDL_Rect> collidables) {
	if (reset) {
		dir.right = 0;
		dir.left = 0;

		pos.x = 64;
		pos.y = 0;

		vel.x = 0;
		vel.y = 0;

		ready_to_jump = 0;
		jump = 0;
		reset = 0;
	}
	// movement and gravity
	const double speed = 300.0;
	double gravity = 60.0;

	if (dir.right) {
		vel.x = speed * dt;
	} else if (dir.left) {
		vel.x = -speed * dt;
	} else {
		vel.x = 0;
	}

	vel.y += (gravity * gravity * dt) * dt;

	// gravity clamp
	vel.y = std::min(13.0, vel.y);

	if (jump && ready_to_jump) {
		vel.y = -13;
		ready_to_jump = 0;
	}


	SDL_Rect player_rectX = hitbox;
	SDL_Rect player_rectY = hitbox;
	player_rectX.x += vel.x;
	player_rectY.y += vel.y;

	double dx = vel.x;
	double dy = vel.y;
	for (SDL_Rect tile : collidables) {
		if (SDL_HasIntersection(&player_rectX, &tile)) {
			dx = 0;
		}

		if (SDL_HasIntersection(&player_rectY, &tile)) {
			if (vel.y > 0) {
				dy = tile.y - (hitbox.y + hitbox.h);
				vel.y = 0;
				ready_to_jump = 1;
			}
			
			if(vel.y < 0) {
				dy = hitbox.y - (tile.y + tile.h);
				vel.y = 0;
			}
		}
	}

	pos.x += dx;
	pos.y += floor(dy);

	// window boundaries
	pos.x = std::max(0.0, pos.x);
	pos.x = std::min((double)WINDOW_WIDTH - hitbox.w, pos.x);

	hitbox.x = round(pos.x);
	hitbox.y = round(pos.y);
}