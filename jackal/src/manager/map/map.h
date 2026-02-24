#pragma once

#include <stdint.h>
#include <stddef.h>

#define CHUNK_WIDTH 32
#define CHUNK_HEIGHT 16
#define CHUNK_LENGTH 16
#define CHUNK_AREA (CHUNK_WIDTH * CHUNK_LENGTH * CHUNK_HEIGHT)

/* Canonical coordinate contract
   - X/Z define the terrain ground plane
   - Y is vertical
   - World space converts to integer block-cell coordinates before chunk lookup
*/
typedef struct CellCoord_t {
    int32_t x;
    int32_t y;
    int32_t z;
} CellCoord_t;

typedef struct ChunkCoord_t {
    int32_t x;
    int32_t z;
} ChunkCoord_t;

typedef struct TerrainLocalCoord_t {
    uint16_t lx;
    uint16_t ly;
    uint16_t lz;
} TerrainLocalCoord_t;


typedef struct Chunk_t {
    uint16_t blockIds[CHUNK_AREA];
    uint16_t flags[CHUNK_AREA];
    ChunkCoord_t coord;
} Chunk_t;

typedef struct Map_t {
    uint16_t mapWidth;
    uint16_t mapLength;
    uint16_t mapHeight;

    Chunk_t* chunkList;
    uint32_t chunkCount;
    uint32_t chunkCap;

    // Render data
    float*   modelBuffer;
    uint32_t modelCount;
}Map_t;

CellCoord_t WorldToCell(float x, float y, float z, float cellSize);
ChunkCoord_t CellToChunkCoord(CellCoord_t cell);
TerrainLocalCoord_t CellToLocalCoord(CellCoord_t cell);
size_t LocalToLinearIndex(TerrainLocalCoord_t local);

Map_t* NewMap(uint16_t width, uint16_t length);
