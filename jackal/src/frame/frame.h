#pragma once

#include <stddef.h>
#include <stdint.h>

#include "render/frame/writer.h"

#define FRAME_MAX_MODELS 1024
#define FRAME_MAX_DIRTY_SPANS 8

typedef struct FrameDirtySpan_t {
	size_t offset;
	size_t size;
} FrameDirtySpan_t;

typedef struct FrameBuildResult_t {
	const void* payload;
	size_t requiredSize;
	uint32_t dirtySpanCount;
	FrameDirtySpan_t dirtySpans[FRAME_MAX_DIRTY_SPANS];
} FrameBuildResult_t;

int BuildFrameModels(FrameBuildResult_t* outResult, const FrameModels_t* models);