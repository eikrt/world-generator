
#ifndef FILE_H_
#define FILE_H_
#include "../world/tile.h"
#include "../world/entity.h"
void saveMap(struct Tile* map, const char* fileName);
void saveEntities(struct Entity* entities, const char* fileName);

struct Tile* openWorld(const char* fileName);
#endif
