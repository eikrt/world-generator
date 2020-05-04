#ifndef APP_H
#define APP_H
#include "SDL2/SDL.h"
#include <string>

SDL_Texture* loadTexture(SDL_Surface* screenSurface, SDL_Surface* renderer, std::string path);
int main();
void init();
void loop(SDL_Window *window, SDL_Surface *screenSurface, SDL_Renderer* renderer, SDL_Texture* tex, SDL_Texture* tex2);
SDL_Surface* loadimage(SDL_Surface* screenSurface, std::string path);
int quit(SDL_Window *window);
#endif
