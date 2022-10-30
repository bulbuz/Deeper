#pragma once

#include <SDL.h>

#include "GameObject.h"
#include "Utils.h"

class Tile : public GameObject {
public:
	int getId();
	void setId(int x);
	Vec2 sprite_sheet_location;

private:
	int id;
};