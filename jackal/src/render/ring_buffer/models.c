#include "models.h"

#include <string.h>
#include "writer.h"


int InitRingBuffer(RingBuffer_t* ring, size_t sliceSize){
	if (!ring || sliceSize == 0) {
		return 0;
	}

	memset(ring, 0, sizeof(RingBuffer_t));
	ring->sliceSize = sliceSize;

	for (uint32_t i = 0; i < BUFFER_COUNT; i++) {
		ring->slices[i].offset = (size_t)i * sliceSize;
		ring->slices[i].size = sliceSize;
	}

	glGenBuffers(1, &ring->ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ring->ssbo);
	glBufferStorage(GL_SHADER_STORAGE_BUFFER, (GLsizeiptr)(sliceSize * BUFFER_COUNT), NULL, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);

	ring->mapped = (uint8_t*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, (GLsizeiptr)(sliceSize * BUFFER_COUNT), GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);

	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	if (!ring->mapped) {
		glDeleteBuffers(1, &ring->ssbo);
		memset(ring, 0, sizeof(RingBuffer_t));
		return 1;
	}

	return 1;
}

void DestroyRingBuffer(RingBuffer_t* ring){
	if (!ring) {
		return;
	}

	for (uint32_t i = 0; i < BUFFER_COUNT; i++) {
		if (ring->slices[i].fence) {
			glDeleteSync(ring->slices[i].fence);
			ring->slices[i].fence = 0;
		}
	}

	if (ring->ssbo) {
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, ring->ssbo);
		glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
		glDeleteBuffers(1, &ring->ssbo);
	}

}



int GetBufferSlice(RingBuffer_t* ring, FrameWriter_t* writer){
	if (!ring || !ring->mapped) {
		return 0;
	}

	if (!ValidWriter(writer) || writer->writeSize > ring->sliceSize){
		return 0;
	}

	uint32_t slice = ring->currentSlice;
	BufferSlice_t* selected = &ring->slices[slice];

	if (selected->fence) {
		while (1) { /*Fix*/
			GLenum result = glClientWaitSync(selected->fence, GL_SYNC_FLUSH_COMMANDS_BIT, 1000000ULL);
			if (result == GL_ALREADY_SIGNALED || result == GL_CONDITION_SATISFIED) {
				break;
			}
		}

		glDeleteSync(selected->fence);
		selected->fence = 0;
	}

	writer->start = ring->mapped + selected->offset;
	writer->offset = selected->offset;
	writer->sliceID = slice;

	ring->currentSlice = (slice + 1) % BUFFER_COUNT;
	return 1;
}


void SendBufferSlice(RingBuffer_t* ring, uint32_t sliceIndex){
	if (!ring || sliceIndex >= BUFFER_COUNT) {
		return;
	}

	BufferSlice_t* slice = &ring->slices[sliceIndex];
	if (slice->fence) {
		glDeleteSync(slice->fence);
	}

	slice->fence = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
}