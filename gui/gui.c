#include "gui.h"
#include "SDL2/SDL.h"
#include "../generator/generator.h"
#include <stdio.h>
#include "../world/tile.h"
#include "../world/entity.h"
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
	struct Entity* entities;
	map = openWorld("../generator/world/map.dat");
	entities = openEntities("../generator/world/entities.dat");
	int rgb[] = {255,255,255};

	SDL_Texture* groundTex = loadTexture(screenSurface, renderer, "../res/ground.bmp", rgb);
	

	SDL_Texture* waterTex = loadTexture(screenSurface, renderer, "../res/water.bmp", rgb);
	SDL_Texture* treeTex = loadTexture(screenSurface, renderer, "../res/tree.bmp", rgb);


	for (int i = 0; i < SIZE; i++){
		
		for (int j = 0; j < SIZE; j++){
			if (map[i*j].height < 1){
	//	int rgb[] = {0,0,0};
			int rgb2[] = {0,100,100};	
			map[i*j].texture = colorTexture(waterTex, rgb2);


//			map[i*j].texture = loadTexture(screenSurface, renderer, "../res/water.bmp", rgb2);
		}
			else {
	//			int rgb[] = {0,0,0};
			int rgb2[] = {200,255,255};	

			map[i*j].texture = colorTexture(groundTex,rgb2);

			//map[i*j].texture = loadTexture(screenSurface, renderer, "../res/ground.bmp", rgb2);
			}
	}
	
	}	


	for (int i = 0; i < ENTITYNUMBER; i++) {
		
			int rgb2[] = {200,55,255};	
			entities[i].texture = colorTexture(treeTex, rgb2);	
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
		for (int i = 0; i < renderX + SCREEN_WIDTH/16; i++) {	
			for (int j = 0; j < renderY + SCREEN_HEIGHT/16; j++) {
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
		for (int i = 0; i < ENTITYNUMBER; i++) {
		
			SDL_Rect renderRect;
			entities[i].rect.x = entities[i].x;
			entities[i].rect.y = entities[i].y;

			renderRect.x = entities[i].rect.x - camera.x;
			renderRect.y = entities[i].rect.y - camera.y;

			renderRect.w = 16;
			renderRect.h = 16;
			
			
               		SDL_RenderCopy( renderer, entities[i].texture, NULL, &renderRect);
	
						
			
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
