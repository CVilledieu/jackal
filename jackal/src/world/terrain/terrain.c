#include "terrain.h"
#include "types.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define RPATH "assets\\objects\\"


static int32_t FloorDiv(int32_t value, int32_t divisor) {
    int32_t quotient = value / divisor;
    int32_t remainder = value % divisor;
    if ((remainder != 0) && ((remainder < 0) != (divisor < 0))) {
        quotient--;
    }
    return quotient;
}

CellCoord_t WorldToCell(float x, float y, float z, float cellSize) {
    CellCoord_t cell = {0, 0, 0};
    if (cellSize <= 0.0f) {
        return cell;
    }

    const float inv = 1.0f / cellSize;
    cell.x = (int32_t)floorf(x * inv);
    cell.y = (int32_t)floorf(y * inv);
    cell.z = (int32_t)floorf(z * inv);
    return cell;
}

ChunkCoord_t CellToChunkCoord(CellCoord_t cell) {
    ChunkCoord_t coord;
    coord.x = FloorDiv(cell.x, CHUNK_WIDTH);
    coord.z = FloorDiv(cell.z, CHUNK_LENGTH);
    return coord;
}

TerrainLocalCoord_t CellToLocalCoord(CellCoord_t cell) {
    TerrainLocalCoord_t local;

    int32_t lx = cell.x % CHUNK_WIDTH;
    int32_t ly = cell.y % CHUNK_HEIGHT;
    int32_t lz = cell.z % CHUNK_LENGTH;

    if (lx < 0) lx += CHUNK_WIDTH;
    if (ly < 0) ly += CHUNK_HEIGHT;
    if (lz < 0) lz += CHUNK_LENGTH;

    local.lx = (uint16_t)lx;
    local.ly = (uint16_t)ly;
    local.lz = (uint16_t)lz;
    return local;
}

size_t LocalToLinearIndex(TerrainLocalCoord_t local) {
    return ((size_t)local.ly * (CHUNK_WIDTH * CHUNK_LENGTH))
         + ((size_t)local.lz * CHUNK_WIDTH)
         + (size_t)local.lx;
}


static inline size_t AreaCheck(uint16_t width, uint16_t length){
    if (width == 0 || length == 0) {
        return 0;
    }
    return (size_t)width * (size_t)length;
}

Terrain_t* NewTerrain(uint16_t width, uint16_t length, uint32_t cap){
    size_t area = AreaCheck(width, length);
    if (!area){
        return NULL;
    }

    Terrain_t* map = malloc(sizeof(Terrain_t));
    if (!map) {
        return NULL;
    }

    map->mapLength = length;
    map->mapWidth = width;
    map->mapHeight = CHUNK_HEIGHT;
    map->chunkCount = 0;
    map->chunkCap = cap;
    map->chunkList = NULL;
    map->modelCount = 0;
    map->modelBuffer = NULL;

    return map;
}


Chunk_t* NewChunk(void){
    Chunk_t* new = calloc(1, sizeof(Chunk_t));
}