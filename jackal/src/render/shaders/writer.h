#pragma once

#include <stdint.h>

typedef struct FrameWriter_t {
    size_t writeSize;
    size_t offset;
    uint32_t sliceID;
    void* write;
} FrameWriter_t;

static inline int ValidWriter(FrameWriter_t* writer){
	if (!writer->write || !writer->offset || !writer->sliceID || !writer->writeSize){
        return 0;
	}
    return 1;
}