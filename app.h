#ifndef APP_H
#define APP_H
#include "SDL2/SDL.h"
#include <string>
int main();
void init();
void loop(SDL_Window *window, SDL_Surface *screenSurface, SDL_Surface *hello);
SDL_Surface* loadimage(SDL_Surface *screenSurface, std::string path);
int quit(SDL_Window *window);
#endif
