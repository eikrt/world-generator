#include "generator.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "../world/tile.h"
#include "../world/entity.h"
#include "../file/file.h"


const int GEN_SEED = 128;

static int noiseFromTable(int* table, int x, int y) { //gets values from lookup table
	int n = table[(y + GEN_SEED) % 256];
	return table[(n+ x) % 256];
}

static float interpol(float x, float y, float s) //vector interpolation
{
	return x + s * (y-x);
}

static float smoothening(float x, float y, float s) // smooths
{
	return interpol(x, y, s * s * (3-2*s));
}

static float noise(int* table,  float x, float y) // gets noise
{
	int x2 = x;
	int y2 = y;
	float x3 = x - x2;
	float y3 = y - y2;
	int s = noiseFromTable(table,x2, y2);
	int t = noiseFromTable(table,x2+1, y2);
	int u = noiseFromTable(table,x2, y2+1);
	int v = noiseFromTable(table,x2+1, y2+1);
	float low = smoothening(s, t, x3);
	float high = smoothening(u, v, x3);
	return smoothening(low, high, y3);
}

static float perlin(float x, float y, float freq, int depth) // main noise function
{
	int tableSize = 256;	
	int table [tableSize];
	srandom(time(0));
	for (int i = 0; i < tableSize; i++) {
			
			table[i] = random()%tableSize;
		}
	float xa = x*freq;
	float ya = y*freq;
	float amplification = 2;
	float val = 0;
	float division = 0.0;

	for(int i=0; i<depth; i++)
	{
      		division += tableSize * amplification;
        	val += noise(table,xa, ya) * amplification;
       		amplification /= 2;
       		xa *= 2;
        	ya *= 2;
	}
	float value = val/division; 
	return value;
}

static struct Tile* createMap(int sealevel){
	static struct Tile map[SIZE*SIZE];
	static struct Tile genmap[SIZE*SIZE];
	int currentChunk = 0;
	//create height map
	for (int i = 0; i <SIZE; i++){

		for (int j = 0; j < SIZE; j++){

			currentChunk = i*j  % CHUNKSIZE;
			int val = perlin(i,j,0.01,1)*100-sealevel;
			int roundVal = floor(val);
			map[(i)*j].height=roundVal;
			genmap[i*j].height = roundVal;
			map[i*j].x = i*16;
			map[i*j].y = j*16;
			if (currentChunk == 1) {
				map[i*j].height = 0;

			}
			printf("%i", currentChunk);
		}
		
	}

	for (int i = 1; i < SIZE-1; i++) {
		for (int j = 1; j < SIZE-1; j++) {
			


			if (genmap[(i-1)*(j-1)].height < 0 && genmap[(i-1)*j].height < 0 && genmap[i *(j-1)].height < 0 && genmap[(i+1)*(j+1)].height < 0&& genmap[(i+1)*j].height <  0 && genmap[i*(j+1)].height < 0){
		//		map[i*j].height = 16;	
			}	
			
		}
	}
	
	
	
	

	//add 	
	return map;
}
static struct Entity* createEntities() {

	static struct Entity entities[ENTITYNUMBER];
	for (int i = 0; i < ENTITYNUMBER; i++) {
			
			entities[i].type = 1;			
			

		}

	return entities;
}
int main(){
	struct Tile* map = createMap(32);
	struct Entity* entities = createEntities();
		
	saveMap(map, "world/map.dat"); // file module 
	saveEntities(entities, "world/entities.dat");
	return 0;	
}

