#include "gui.h"
#include "SDL2/SDL.h"
#include "../generator/generator.h"
#include <stdio.h>
#include <string>
#include "../world/tile.h";
const int SCREEN_WIDTH = 640*2;
const int SCREEN_HEIGHT = 480*2;
struct Camera{
	int x;
	int y;
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
	struct Camera camera;
	camera.x = 0;
	camera.y = 0;
	SDL_Event e;
		
	
	

	char ch;
	int size = 0;
	FILE* fp1 = fopen("../generator/map/map.txt", "r");
	while ((ch = getc(fp1)) != '\n') {
		size++;
	}
	fclose(fp1);
	
	struct Tile tiles[size][size];
	FILE* fp;
	fp = fopen("../generator/map/map.txt", "r");	
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
			if (ch == '0' || ch == '1' || ch == '2'||ch == '3'|| ch == '4'|| ch == '5')
				tiles[charAt][lines].texture = loadTexture(screenSurface,renderer,"../res/tile.bmp");
			else
			
				tiles[charAt][lines].texture = loadTexture(screenSurface,renderer,"../res/ground.bmp");

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
else if( e.type == SDL_KEYDOWN )
                    {
                        //Select surfaces based on key press
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

		for (int i = 0; i < size; i++) {	
			for (int j = 0; j < size; j++) {
				
				SDL_Rect renderRect;

				renderRect.x = tiles[i][j].rect.x-camera.x;
				renderRect.y = tiles[i][j].rect.y-camera.y;
				renderRect.h = 16;
				renderRect.w = 16;
               			SDL_RenderCopy( renderer, tiles[i][j].texture, NULL, &renderRect);
			
			}		
		}

		SDL_RenderPresent(renderer);		
	
	SDL_Delay(100);
}	
quit(window);
	
}
int quit(SDL_Window *window){
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
