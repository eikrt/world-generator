#include "gui.h"
#include "SDL2/SDL.h"
#include "../generator/generator.h"
#include <stdio.h>
#include <string>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
struct Tile{
	char height;
	SDL_Rect rect;
};
SDL_Surface* loadImage(SDL_Surface* screenSurface, std::string path){

	SDL_Surface* betterSurface = NULL;
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL) {
		printf("image loading failed");
	}
//	else {
//		betterSurface = SDL_ConvertSurface(loadedSurface,screenSurface->format, 0);
//		if (betterSurface == NULL) {
//			printf("image optimizing failed");
//		}
//			SDL_FreeSurface (loadedSurface);
//	}
	return loadedSurface;

}


SDL_Texture* loadTexture(SDL_Surface* screenSurface, SDL_Renderer* renderer, std::string path) {
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = loadImage(screenSurface,path);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
		
}


int main() {
	init();
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;
	SDL_Texture* texture2 = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

		printf("SDL couldn't initialize");	
	}
	else {
		window = SDL_CreateWindow( "Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED);       		
		if( window == NULL ) {
            	printf( "Error: %s\n", SDL_GetError());
        	}
		screenSurface = SDL_GetWindowSurface(window);

		texture = loadTexture(screenSurface, renderer, "../res/tile.bmp");
		texture2 = loadTexture(screenSurface, renderer, "../res/ground.bmp");
		

		SDL_SetRenderDrawColor(renderer, 0xFF,0xFF, 0xFF, 0xFF);
////		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF,0xFF,0xFF));


//		SDL_UpdateWindowSurface(window);
	
	

	}
	loop(window, screenSurface, renderer, texture,texture2);
	return 0;
}

void init(){
	
}
void loop(SDL_Window *window, SDL_Surface *screenSurface, SDL_Renderer* renderer, SDL_Texture* tex, SDL_Texture* tex2){
	bool running = true;
	SDL_Event e;
	
	struct Tile tiles[64][64];
	FILE* fp;
	fp = fopen("/home/eino/repo/world-generator/generator/map/map.txt", "r");	
	if (fp == NULL) {
		printf("error while opening file");
	}

	char ch;
	for (int i = 0; i < 64; i++) {		
		for (int j = 0; j < 64; j++) {
			ch = getc(fp);
			tiles[i][j].height = ch;
			tiles[i][j].rect.x = i*16;
			tiles[i][j].rect.y = j*16;
			tiles[i][j].rect.w = 16;
			tiles[i][j].rect.h = 16;
	}
	}
	fclose(fp);
	while(running) {
		while (SDL_PollEvent(&e) != 0)
			{

			if (e.type == SDL_QUIT){
				running = false;
			}
		}
		SDL_RenderClear( renderer );

		for (int i = 0; i < 64; i++) {	
			for (int j = 0; j < 64; j++) {
				if (tiles[i][j].height == '0')						
               				SDL_RenderCopy( renderer, tex, NULL, &tiles[i][j].rect);
				else
               				SDL_RenderCopy( renderer, tex2, NULL, &tiles[i][j].rect);

			}		
		}

		SDL_RenderPresent(renderer);		
	}	
quit(window);
}
int quit(SDL_Window *window){
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
