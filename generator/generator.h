#ifndef GENERATOR_H_
#define GENERATOR_H_
#define SIZE 64
int noiseFromTable(int* table,int x, int y);
float interpol(float x, float y, float s);
float smoothening(float x, float y, float s);
float noise(int* table, float x, float y);
float perlin(float x, float y, float freq, int depth);
struct Tile* createMap(int sealevel);
int main();
#endif
