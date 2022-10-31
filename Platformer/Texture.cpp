#include "Texture.h"
#include "Utils.h"

Texture::Texture() {
	WIDTH = 0;
	HEIGHT = 0;
	texture = nullptr;
}

Texture::~Texture() {
	free();
}

void Texture::free() {
	if (texture != nullptr) {
		WIDTH = 0;
		HEIGHT = 0;
		texture = nullptr;
	}
}

void Texture::load_TextureFromFile(SDL_Renderer* renderer, std::string filePath) {
	free();

	SDL_Texture* finalTexture = nullptr;
	SDL_Surface* loadedSurface = nullptr;

	loadedSurface = IMG_Load(filePath.c_str());
	
	if (loadedSurface == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, SDL_GetError());
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0, 0));
		finalTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		
		if (finalTexture == nullptr) {
			SDL_LogError(SDL_LOG_CATEGORY_ERROR, SDL_GetError());
		}
		else {
			WIDTH = loadedSurface->w * 4;
			HEIGHT = loadedSurface->h * 4;
		}
		SDL_FreeSurface(loadedSurface);
	}

	texture = finalTexture;
}

void Texture::render(SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, int scale) {
	SDL_Rect renderRect{x, y, WIDTH * scale, HEIGHT * scale};

	if (clip != nullptr) {
		renderRect.w = clip->w * scale;
		renderRect.h = clip->h * scale;
	}

	SDL_RenderCopy(renderer, texture, clip, &renderRect);
}

int Texture::getWidth() {
	return WIDTH;
}

int Texture::getHeight() {
	return HEIGHT;
}
