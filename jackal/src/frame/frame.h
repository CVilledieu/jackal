#pragma once

#include <stddef.h>
#include <stdint.h>

#include "render/writer.h"

#define FRAME_MAX_MODELS 1024
#define FRAME_MAX_DIRTY_SPANS 8
#define FRAME_MAX_MESH_TRACKS FRAME_MAX_MODELS

typedef struct FrameDirtySpan_t {
	size_t offset;
	size_t size;
} FrameDirtySpan_t;

typedef struct FrameMeshTrack_t {
	int meshID;
	uint32_t modelStart;
	uint32_t modelCount;
} FrameMeshTrack_t;

typedef struct FrameBuildResult_t {
	const void* payload;
	size_t requiredSize;
	uint32_t dirtySpanCount;
	FrameDirtySpan_t dirtySpans[FRAME_MAX_DIRTY_SPANS];
	uint32_t meshTrackCount;
	FrameMeshTrack_t meshTracks[FRAME_MAX_MESH_TRACKS];
} FrameBuildResult_t;

int BuildFrameModels(FrameBuildResult_t* outResult, const FrameModels_t* models);