#include "GameObject.h"

void GameObject::init(SDL_Rect dimensions) {
	pos.x = dimensions.x;
	pos.y = dimensions.y;

	hitbox = dimensions;
}

void GameObject::render(SDL_Renderer* renderer) {
	texture.render(renderer, pos.x, pos.y);
}

void GameObject::load_Texture(SDL_Renderer* renderer, std::string path) {
	texture.load_TextureFromFile(renderer, path);
}
