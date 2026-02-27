#pragma

#include <stdint.h>

#define BUFFER_COUNT 3

typedef enum BufferState_e {
    BUFFER_FREE = 0,
    BUFFER_BUSY,
} BufferState_e;

typedef struct ModelBufferRoles_t{
    uint8_t render_index;
    uint8_t model_index;
    uint8_t staging_index;
} ModelBufferRoles_t;

typedef struct ModelBuffer_t{
    BufferState_e state;
    size_t size;
    float* buffer;
} ModelBuffer_t;

typedef struct BufferSystem_t {
    ModelBuffer_t
} BufferSystem_t;