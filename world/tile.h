#ifndef TILE_H
#define TILE_H
#include "SDL2/SDL.h"
struct Tile{
	char height;	
	SDL_Texture* texture;
	SDL_Rect rect;
};
#endif
