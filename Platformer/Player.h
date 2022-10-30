#pragma once

#include <algorithm>
#include <vector>

#include "Utils.h"
#include "GameObject.h"

class Player : public GameObject {
public:
	Player();
	void update(double dt);
	Dir dir;
	Vec2 vel;

};