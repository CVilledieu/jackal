#pragma once


typedef struct ComponentData_t{
    unsigned int uniformIndex;
    unsigned int VAO;
    unsigned int drawLength;
} ComponentData_t;

/* NOTE: refactor to array/list based on the number of VAO?*/
typedef struct FrameData_t {
    ComponentData_t map; 
    ComponentData_t entities;
} FrameData_t;