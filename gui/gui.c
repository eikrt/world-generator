#include "app.h"
#include "SDL2/SDL.h"
#include <stdio.h>
#include <string>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Surface* loadImage(SDL_Surface* screenSurface, std::string path){

	SDL_Surface* betterSurface = NULL;
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL) {
		printf("image loading failed");
	}
	else {
		betterSurface = SDL_ConvertSurface(loadedSurface,screenSurface->format, 0);
		if (betterSurface == NULL) {
			printf("image optimizing failed");
		}
			SDL_FreeSurface (loadedSurface);
	}
	return betterSurface;

}
int main() {
	init();
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Surface* hello = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

		printf("SDL couldn't initialize");	
	}
	else {
		window = SDL_CreateWindow( "Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Error: %s\n", SDL_GetError());
        }
	screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF,0xFF,0xFF));
	hello = loadImage(screenSurface, "res/tile.bmp");
	if (hello == NULL){
		printf("failed to load img");

	}

	SDL_UpdateWindowSurface(window);
	
	

	}
	loop(window, screenSurface,hello);
	return 0;
}

void init(){
	
}
void loop(SDL_Window *window, SDL_Surface *screenSurface, SDL_Surface *hello){
	bool running = true;
	SDL_Event e;
	while(running) {
		while (SDL_PollEvent(&e) != 0)
			{

			if (e.type == SDL_QUIT){
				running = false;
			}
		}
			
		SDL_BlitSurface(hello, NULL, screenSurface, NULL);
		SDL_UpdateWindowSurface(window);
	}	
quit(window);
}
int quit(SDL_Window *window){
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
