#ifndef GENERATOR_H_
#define GENERATOR_H_
#define SIZE 512
#define CHUNKSIZE 64
#define CHUNKS 8
#define ENTITYNUMBER 128
static int noiseFromTable(int* table,int x, int y);
static float interpol(float x, float y, float s);
static float smoothening(float x, float y, float s);
static float noise(int* table, float x, float y);
static float perlin(float x, float y, float freq, int depth);
static struct Tile* createMap(int sealevel);
int main();
#endif
