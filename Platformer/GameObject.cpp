#include "GameObject.h"
#include <iostream>

void GameObject::init(SDL_Rect dimensions) {
	hitbox = dimensions;

	if (pos.x && pos.y) {
		hitbox.x = pos.x;
		hitbox.y = pos.y;
	} else {
		pos.x = dimensions.x;
		pos.y = dimensions.y;
	}
}

void GameObject::render(SDL_Renderer* renderer) {
	texture.render(renderer, pos.x, pos.y);
}

void GameObject::load_Texture(SDL_Renderer* renderer, std::string path) {
	texture.load_TextureFromFile(renderer, path);
}

// debug
void GameObject::draw_hitbox(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer, &hitbox);
}
