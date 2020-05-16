#include "imgload.h"
#include "SDL2/SDL.h"
#include <stdio.h>
SDL_Surface* loadImage(SDL_Surface* screenSurface, const char* path){

	SDL_Surface* betterSurface = NULL;
	SDL_Surface* loadedSurface = SDL_LoadBMP(path);
	if (loadedSurface == NULL) {
		printf("image loading failed");
	}
	return loadedSurface;

}


SDL_Texture* loadTexture(SDL_Surface* screenSurface, SDL_Renderer* renderer, const char* path, int rgb[3]) {
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = loadImage(screenSurface,path);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_SetTextureColorMod(texture, rgb[0], rgb[1], rgb[2] );
	SDL_FreeSurface(surface);
	return texture;
		
}
