#ifndef ENTITY_H
#define ENTITY_H
#include "SDL2/SDL.h"
struct Entity{
	char height;
	unsigned int type;
	int x;
	int y;	
	SDL_Texture* texture;
	SDL_Rect rect;
};
#endif
