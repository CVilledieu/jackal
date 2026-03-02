#pragma once

#include <stdint.h>

// Row-major order refrence
//  0  1  2  3 
//  4  5  6  7
//  8  9 10 11
// 12 13 14 15

// Using vector and matrix defines for index count instead of typedefing a float array of that size for code clarity

#define VEC4 4
#define MAT4 16

#define BASE_MATRIX { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 }


// Common type aliases used across all systems
typedef uint16_t MeshId;
typedef uint8_t  MaterialId;
typedef float VEC2[2]; 
typedef float VEC3[3];
typedef float MAT4_t[16];
#define MESH_INVALID ((MeshId)0xFFFF)



// Tile shape enum – determines collision geometry for a single tile
typedef enum TileShape {
    TILE_PASSABLE  = 0,
    TILE_SOLID     = 1,
    TILE_SLOPE_N   = 2,
    TILE_SLOPE_S   = 3,
    TILE_SLOPE_E   = 4,
    TILE_SLOPE_W   = 5,
    TILE_HALF      = 6,
    TILE_SHAPE_COUNT
} TileShape;


// Vertex format matching the shader layout (11 floats, 44 bytes)
typedef struct Vertex_t {
    VEC3 position;
    VEC3 normal;
    VEC3 color;
    VEC2 texCoord;
} Vertex_t;

#define VERTEX_STRIDE sizeof(Vertex_t)

