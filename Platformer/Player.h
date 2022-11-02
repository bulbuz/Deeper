#pragma once

#include <algorithm>
#include <vector>
#include <iostream>

#include "Utils.h"
#include "GameObject.h"

class Player : public GameObject {
public:
	Player();
	void update(double dt, std::vector<SDL_Rect> collidables);
	Dir dir;
	Vec2 vel;
	bool jump;
	bool reset; // debugging
private:
	bool ready_to_jump;
};