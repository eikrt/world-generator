#include "gui.h"
#include "SDL2/SDL.h"
#include "../generator/generator.h"
#include <stdio.h>
#include "../world/tile.h"
#include "../file/file.h"
#include "../io/imgload.h"
const int SCREEN_WIDTH = 512*2;
const int SCREEN_HEIGHT = 288*2;
struct Camera{
	int x;
	int y;
};

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
	int running = 1;
	struct Camera camera;
	camera.x = 0;
	camera.y = 0;
	SDL_Event e;
	struct Tile* map;
	map = openWorld("../generator/map/map.dat");
	
	int rgb = {255,255,255};

	SDL_Texture* groundTex = loadTexture(screenSurface, renderer, "../res/ground.bmp", rgb);
	SDL_Texture* waterTex = loadTexture(screenSurface, renderer, "../res/water.bmp", rgb);
	for (int i = 0; i < SIZE; i++){
		
		for (int j = 0; j < SIZE; j++){
			if (map[i*j].height < 1){
	//	int rgb[] = {0,0,0};	
		//	int rgb[] = {0,100-0.8*map[i*j].height,100-0.4*map[i*j].height};	

			map[i*j].texture = groundTex;
		}
			else {
	//			int rgb[] = {0,0,0};
		//	int rgb[] = {200-0.8*map[i*j].height,255-0.8*map[i*j].height,255-0.4*map[i*j].height};	

			map[i*j].texture = waterTex;

			}
	}
	
	}	




	while(running==1) {
		
		while (SDL_PollEvent(&e) != 0)
			{

			if (e.type == SDL_QUIT){
				running = 0;
			}
else if( e.type == SDL_KEYDOWN )
                    {
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_UP:
                            camera.y -= 16;
				break;
                            case SDLK_DOWN:
                            camera.y += 16;
                            break;
                            case SDLK_LEFT:
                            camera.x -= 16;
                            break;
                            case SDLK_RIGHT:
                            camera.x += 16;
                            break;
			}
		}
}
		SDL_RenderClear( renderer );
		int renderX = camera.x / 16;
		int renderY = camera.y / 16;
		for (int i = 0; i < renderY + SCREEN_HEIGHT/16; i++) {	
			for (int j = 0; j < renderX + SCREEN_WIDTH/16; j++) {
				if (i > 0 && j > 0 && i < SIZE + renderY&& j < SIZE + renderX) {

					SDL_Rect renderRect;
					map[i*j].rect.x = i*16;
					map[i*j].rect.y = j*16;	
					renderRect.x = map[i*j].rect.x-camera.x;
					renderRect.y = map[i*j].rect.y-camera.y;
					renderRect.h = 16;
					renderRect.w = 16;
               				SDL_RenderCopy( renderer, map[i*j].texture, NULL, &renderRect);
				}
			}		
		}
		SDL_RenderPresent(renderer);		
	SDL_Delay(32);
}	
quit(window);
}
int quit(SDL_Window *window){
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
