#pragma once

#include "mesh.h"

#define MAX_MAP_MODELS 16
#define MAX_ENTITY_MODELS 16

typedef struct MapDrawData_t{
    float models[MAX_MAP_MODELS];
    int material[MAX_MAP_MODELS];
} MapDrawData_t;

typedef struct EntityDrawData_t{
    float models[MAX_ENTITY_MODELS];
    int material[MAX_ENTITY_MODELS];
} EntityDrawData_t;

typedef struct FrameModels_t{
    MapDrawData_t mapData;
    EntityDrawData_t entityData;
}FrameModels_t;



/* NOTE: refactor to array/list based on VAO count need*/
typedef struct Frame_t {
    Mesh_t map;
    Mesh_t entity;
} Frame_t;
