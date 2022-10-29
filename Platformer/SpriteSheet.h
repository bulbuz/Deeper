#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <string>

#include "Texture.h"

class Spritesheet
{
public:
    Spritesheet(std::string path, int row, int column);
    ~Spritesheet();

    Texture get_SelectedSprite(int x, int y);

private:
    SDL_Rect     m_clip;
    SDL_Surface *m_spritesheet_image;
};
