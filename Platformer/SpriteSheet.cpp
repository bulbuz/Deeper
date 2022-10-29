#include "SpriteSheet.h"

Spritesheet::Spritesheet(std::string path, int row, int column)
{
    m_spritesheet_image = IMG_Load(path.c_str());

    m_clip.w = m_spritesheet_image->w / column;
    m_clip.h = m_spritesheet_image->h / row;
}

Spritesheet::~Spritesheet()
{
    SDL_FreeSurface(m_spritesheet_image);
}

Texture Spritesheet::get_SelectedSprite(int x, int y)
{
    m_clip.x = x * m_clip.w;
    m_clip.y = y * m_clip.h;
}

