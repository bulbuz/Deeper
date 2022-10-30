#include "Player.h"
#include <iostream>

Player::Player() {
	dir.right = 0;
	dir.left = 0;

	pos.x = 0.0;
	pos.y = 0.0;

	vel.x = 80;
	vel.y = 0;
}

void Player::update(double dt) {
	// movement and gravity
	const double gravity = 150.0;

	if(dir.right)
		pos.x += ((double)vel.x* dt);

	if(dir.left)
		pos.x -= ((double)vel.x* dt);

	pos.y += vel.y * dt + dt * 0.5 * (gravity + (double)gravity * dt);
	vel.y += gravity * dt;
	vel.y = std::min(100.0, vel.y);

	hitbox.x = round(pos.x);
	hitbox.y = round(pos.y);

}