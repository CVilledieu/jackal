#pragma once

#include <stdint.h>

#define CURRENT_VERSION ((uint8_t)0u)

uint32_t GetFileData(uint8_t** dest, const char* rPath, const char* fName);
void GetPathData(void);

