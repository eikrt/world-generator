#include "generator.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "../world/tile.h"
#include "../file/file.h"


const int GEN_SEED = 64;

int noiseFromTable(int* table, int x, int y) { //gets values from lookup table
	int n = table[(y + GEN_SEED) % 256];
	return table[(n+ x) % 256];
}

float interpol(float x, float y, float s) //vector interpolation
{
	return x + s * (y-x);
}

float smoothening(float x, float y, float s) // smooths
{
	return interpol(x, y, s * s * (3-2*s));
}

float noise(int* table,  float x, float y) // gets noise
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

float perlin(float x, float y, float freq, int depth) // main noise function
{
	
	int table [256];
	srandom(time(0));
	for (int i = 0; i < 256; i++) {
			
			table[i] = random()%256;
		}
	float xa = x*freq;
	float ya = y*freq;
	float amplification = 1.0;
	float val = 0;
	float division = 0.0;

	for(int i=0; i<depth; i++)
	{
      		division += 256 * amplification;
        	val += noise(table,xa, ya) * amplification;
       		amplification /= 2;
       		xa *= 2;
        	ya *= 2;
	}
	float value = val/division; 
	return value;
}

struct Tile* createMap(int sealevel){
	static struct Tile map[SIZE*SIZE];
	for (int i = 0; i <SIZE; i++){
		for (int j = 0; j < SIZE; j++){
		int val = perlin(i,j,0.1,1)*100-sealevel;
		int roundVal = floor(val);
		map[(i)*j].height=roundVal;

		map[i*j].x = i*16;
		map[i*j].y = j*16;
		}
		
	}
	return map;
}

int main(){
	struct Tile* map = createMap(32);
	saveWorld(map, "map/map.dat");
	openWorld("map/map.dat");
	return 0;	
}

