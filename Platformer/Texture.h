#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Texture {
public:
	Texture();
	~Texture();

	void load_TextureFromFile(SDL_Renderer* renderer, std::string filePath);
	void free();
	void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip = nullptr);

	int getWidth();
	int getHeight();

private:
	SDL_Texture* texture;

	int WIDTH;
	int HEIGHT;
};