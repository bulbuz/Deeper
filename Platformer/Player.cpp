#include "Player.h"

Player::Player() {
	dir.right = 0;
	dir.left = 0;

	vel = 100;
}

void Player::update(double dt) {
	if (dir.right) {
		pos.x += round((double)vel * dt);
	}
	if (dir.left) {
		pos.x -= round((double)vel * dt);
	}
}