#include "frame.h"

#include <string.h>

typedef struct FrameGpuDraw_t {
	float model[16];
} FrameGpuDraw_t;

static FrameGpuDraw_t gFrameScratch[FRAME_MAX_MODELS];

static inline uint32_t ClampModelCount(int totalModels){
	if (totalModels <= 0) {
		return 0;
	}

	if ((uint32_t)totalModels > FRAME_MAX_MODELS) {
		return FRAME_MAX_MODELS;
	}

	return (uint32_t)totalModels;
}

static inline void ZeroResult(FrameBuildResult_t* outResult){
	outResult->payload = gFrameScratch;
	outResult->requiredSize = 0;
	outResult->dirtySpanCount = 0;
	outResult->meshTrackCount = 0;
}

static inline void TrackMeshOrder(FrameBuildResult_t* outResult, const FrameModels_t* models, uint32_t modelCount){
	if (!models->modelData) {
		return;
	}

	for (uint32_t i = 0; i < modelCount; i++) {
		const int meshID = models->modelData[i].meshID;

		if (outResult->meshTrackCount > 0) {
			FrameMeshTrack_t* lastTrack = &outResult->meshTracks[outResult->meshTrackCount - 1];
			if (lastTrack->meshID == meshID) {
				lastTrack->modelCount++;
				continue;
			}
		}

		if (outResult->meshTrackCount >= FRAME_MAX_MESH_TRACKS) {
			break;
		}

		FrameMeshTrack_t* nextTrack = &outResult->meshTracks[outResult->meshTrackCount++];
		nextTrack->meshID = meshID;
		nextTrack->modelStart = i;
		nextTrack->modelCount = 1;
	}
}

int BuildFrameModels(FrameBuildResult_t* outResult, const FrameModels_t* models){
	if (!outResult || !models) {
		return 0;
	}

	ZeroResult(outResult);

	const uint32_t modelCount = ClampModelCount(models->totalModels);
	if (modelCount == 0) {
		return 1;
	}

	outResult->requiredSize = (size_t)modelCount * sizeof(FrameGpuDraw_t);
	TrackMeshOrder(outResult, models, modelCount);

	if (!models->dirty || !models->modelData) {
		return 1;
	}

	uint32_t start = 0;
	uint32_t count = modelCount;

	if (models->dirtyCount > 0) {
		start = models->dirtyStart;
		if (start >= modelCount) {
			return 1;
		}

		count = models->dirtyCount;
		if ((start + count) > modelCount) {
			count = modelCount - start;
		}
	}

	for (uint32_t i = start; i < (start + count); i++) {
		if (models->modelData[i].model) {
			memcpy(gFrameScratch[i].model, models->modelData[i].model, sizeof(gFrameScratch[i].model));
			continue;
		}

		memset(gFrameScratch[i].model, 0, sizeof(gFrameScratch[i].model));
	}

	outResult->dirtySpanCount = 1;
	outResult->dirtySpans[0].offset = (size_t)start * sizeof(FrameGpuDraw_t);
	outResult->dirtySpans[0].size = (size_t)count * sizeof(FrameGpuDraw_t);
	return 1;
}