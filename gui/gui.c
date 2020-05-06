#include "gui.h"
#include "SDL2/SDL.h"
#include "../generator/generator.h"
#include <stdio.h>
#include <string>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
struct Tile{
	char height;	
	SDL_Texture* texture = NULL;
	SDL_Rect rect;
};
SDL_Surface* loadImage(SDL_Surface* screenSurface, std::string path){

	SDL_Surface* betterSurface = NULL;
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL) {
		printf("image loading failed");
	}
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
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

		printf("SDL couldn't initialize");	
	}
	else {
		window = SDL_CreateWindow( "World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED);       		
		if( window == NULL ) {
            	printf( "Error: %s\n", SDL_GetError());
        	}
		screenSurface = SDL_GetWindowSurface(window);
		SDL_SetRenderDrawColor(renderer, 0xFF,0xFF, 0xFF, 0xFF);

	}
	loop(window, screenSurface, renderer);
	return 0;
}

void init(){
	
}
void loop(SDL_Window *window, SDL_Surface *screenSurface, SDL_Renderer* renderer){
	bool running = true;
	SDL_Event e;
		
	
	
	struct Tile tiles[32][32];
	char ch;
	int size = 0;
	FILE* fp1 = fopen("/home/eino/repo/world-generator/generator/map/map.txt", "r");
	while ((ch = getc(fp1)) != '\n') {
		size++;
	}
	fclose(fp1);
	
	FILE* fp;
	fp = fopen("/home/eino/repo/world-generator/generator/map/map.txt", "r");	
	if (fp == NULL) {
		printf("error while opening file");
	}

	int lines = 0;
	int charAt = 0;
	char c;

	while(lines <size) {

			ch = getc(fp);	




			tiles[charAt][lines].height = ch;
			tiles[charAt][lines].rect.x = charAt*16;
			tiles[charAt][lines].rect.y = lines*16;
			tiles[charAt][lines].rect.w = 16;
			tiles[charAt][lines].rect.h = 16;
			if (ch == '0')
				tiles[charAt][lines].texture = loadTexture(screenSurface,renderer,"/home/eino/repo/world-generator/res/tile.bmp");
			else
			
				tiles[charAt][lines].texture = loadTexture(screenSurface,renderer,"/home/eino/repo/world-generator/res/ground.bmp");

			charAt++;
			if (charAt == size) {
				lines++;
				charAt = 0;
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

		for (int i = 0; i < size; i++) {	
			for (int j = 0; j < size; j++) {
               			SDL_RenderCopy( renderer, tiles[i][j].texture, NULL, &tiles[i][j].rect);
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
