#pragma once

#include <SDL.h>
#include "GameObject.h"

class Tile : public GameObject {
public:
	int getId();
	void setId(int x);

private:
	int id;

};