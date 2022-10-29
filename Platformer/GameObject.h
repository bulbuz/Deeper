#pragma once

#include <SDL.h>
#include <string>
#include "Utils.h"
#include "Texture.h"

class GameObject {
public:
	virtual void update();
	void render(SDL_Renderer* renderer);
	void load_Texture(SDL_Renderer* renderer, std::string path);
	void init(SDL_Rect* dimensions);

	Vec2 pos;
	SDL_Rect hitbox;
	Texture texture;
};