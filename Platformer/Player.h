#pragma once

#include <math.h>

#include "Utils.h"
#include "GameObject.h"

class Player : public GameObject {
public:
	Player();
	Dir dir;
	void update(double dt);

private:
	int vel;
};